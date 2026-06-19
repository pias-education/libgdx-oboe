#include "file_asset.hpp"
#include "../utility/log.hpp"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace {
// The avio opaque is a heap-allocated std::shared_ptr<int> sharing ownership of the fd
// with the owning file_asset. This keeps the fd alive for as long as either the
// file_asset or the avio context lives, and closing happens via the shared_ptr deleter.
int avio_fd(void *opaque) {
    return **static_cast<std::shared_ptr<int> *>(opaque);
}

int file_read(void *opaque, uint8_t *buf, int buf_size) {
    ssize_t bytes_read = ::read(avio_fd(opaque), buf, static_cast<size_t>(buf_size));
    if (bytes_read < 0) {
        return AVERROR(errno);
    } else if (bytes_read == 0) {
        return AVERROR_EOF;
    }
    return static_cast<int>(bytes_read);
}

int64_t file_seek(void *opaque, int64_t offset, int whence) {
    int fd = avio_fd(opaque);
    switch (whence & ~AVSEEK_FORCE) {
        case AVSEEK_SIZE: {
            struct stat st {};
            if (::fstat(fd, &st) != 0) {
                return AVERROR(errno);
            }
            return static_cast<int64_t>(st.st_size);
        }
        default: {
            off_t pos = ::lseek(fd, static_cast<off_t>(offset), whence & ~AVSEEK_FORCE);
            return pos < 0 ? AVERROR(errno) : static_cast<int64_t>(pos);
        }
    }
}
}

file_asset_result file_asset::create(std::string_view path) {
    // string_view may not be null-terminated, so materialise it before open().
    std::string native_path(path);
    int fd = ::open(native_path.c_str(), O_RDONLY);
    if (fd < 0) {
        return make_error("Can't open a file: {} ({})", native_path, std::strerror(errno));
    }
    return ok(file_asset(native_path, fd));
}

file_asset::file_asset(std::string_view path, int fd)
        : m_fd(new int(fd), [](int *p) {
              if (p) {
                  if (*p >= 0) ::close(*p);
                  delete p;
              }
          })
        , m_path(path) {}

avio_context_ptr file_asset::generate_avio() {
    int buf_size = 1024 * 4;
    auto *buffer = static_cast<unsigned char *>(av_malloc(buf_size));
    auto *opaque = new std::shared_ptr<int>(m_fd);
    auto *ctx = avio_alloc_context(buffer, buf_size, 0, opaque, &file_read, nullptr, &file_seek);
    return avio_context_ptr(ctx, [](AVIOContext *c) {
        delete static_cast<std::shared_ptr<int> *>(c->opaque);
        av_free(c->buffer);
        av_free(c);
    });
}
