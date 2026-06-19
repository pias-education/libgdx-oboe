#pragma once

#include <memory>
#include <string_view>
#include <string>

#include "ffmpeg_utils.hpp"
#include "../utility/result_utils.hpp"

extern "C" {
#include <libavformat/avformat.h>
}

SIMPLE_RESULT(file_asset)

/// Utility class to tie together a filesystem file (Absolute/Local/External paths)
/// with an avio context for reading. Mirrors @p internal_asset, but reads through a
/// raw file descriptor instead of an AAsset.
///
/// This exists because FFmpeg's built-in `file:` protocol is not compiled into the
/// self-built libavformat shipped with this library, so a bare path handed to
/// avformat_open_input fails with "Protocol not found". Feeding the demuxer through a
/// custom AVIOContext (AVFMT_FLAG_CUSTOM_IO) — exactly how internal assets are read —
/// sidesteps the protocol layer entirely.
class file_asset {
public:
    /// Try to open a file for reading
    /// @param path Filesystem path (need not be null-terminated)
    static file_asset_result create(std::string_view path);

    /// Generates a working avio context for reading/seeking the file. The returned
    /// context owns a reference to the file descriptor and closes it on destruction.
    /// @return RAII avio context
    avio_context_ptr generate_avio();

    const std::string& path() const { return m_path; }

private:
    file_asset(std::string_view path, int fd);

    /// Owns the fd; the custom deleter closes it once the last reference is gone.
    std::shared_ptr<int> m_fd;
    const std::string m_path;
};
