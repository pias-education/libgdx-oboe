#include "buffer_player.hpp"
#include "../utility/log.hpp"
#include <vector>

using namespace opensl;

inline void get_interface(SLObjectItf p_player, const SLInterfaceID p_id,
                          void* p_interface, std::string_view p_id_desc) {
    auto result = (*p_player)->GetInterface(p_player, p_id, p_interface);
    if(result != SL_RESULT_SUCCESS) error("Cannot access interface \"{}\" in opensl::buffer_player.", p_id_desc);
}

buffer_player::buffer_player(const context& p_context, SLDataSource p_source)
    : m_queue_buffer(192) {
    std::vector<SLInterfaceID> ids { SL_IID_PLAY, SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
    std::vector<SLboolean> req { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

    SLDataLocator_AndroidSimpleBufferQueue loc_bq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
    SLDataFormat_PCM pcm = {
        .formatType = SL_DATAFORMAT_PCM,
        // TODO dynamic channels
        .numChannels = 2,
        // OpenSL ES for Android doesn't perform resampling, so
        // it's advisable by google to use 44.1Hz to match the device,
        // and it's most likely that 44.1Hz is how files are sampled anyways.
        .samplesPerSec = SL_SAMPLINGRATE_44_1,
        // Floats only from API 21
        .bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16,
        .containerSize = SL_PCMSAMPLEFORMAT_FIXED_16,
        // TODO dynamic channels
        .channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
        // Little Endian only on OpenSL ES for Android
        .endianness = SL_BYTEORDER_LITTLEENDIAN
    };
    SLDataSink sink = { &loc_bq, &pcm };

    auto engine = p_context.engine();
    auto result = (*engine)->CreateAudioPlayer(engine, &m_player,
                                               &p_source, &sink,
                                               ids.size(), ids.data(), req.data());
    if(result != SL_RESULT_SUCCESS) error("Can't create an audio buffer_player in opensl::buffer_player !");
    (*m_player)->Realize(m_player, SL_BOOLEAN_FALSE);

    get_interface(m_player, SL_IID_PLAY, &m_play, "SL_IID_PLAY");
    get_interface(m_player, SL_IID_SEEK, &m_seek, "SL_IID_SEEK");
    get_interface(m_player, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &m_queue, "SL_IID_ANDROIDSIMPLEBUFFERQUEUE");

    (*m_queue)->RegisterCallback(m_queue, [](const SLBufferQueueItf p_queue, void* p_self) {
        auto self = reinterpret_cast<buffer_player*>(p_self);
        if(self->m_buffer_callback) {
            self->m_buffer_callback(self->m_queue_buffer);
        }
    }, this);
}

buffer_player::~buffer_player() {
    (*m_play)->SetPlayState(m_play, SL_PLAYSTATE_STOPPED);
    (*m_player)->Destroy(m_player);
}

void buffer_player::on_buffer_update(buffer_callback p_callback) {
    m_buffer_callback = p_callback;
}

void buffer_player::enqueue() {
    // capacity * 2: because this argument in 8 bits, but buffer is in 16 bits
    (*m_queue)->Enqueue(m_queue, m_queue_buffer.data(), m_queue_buffer.capacity() * 2);
}

void buffer_player::resize_buffer(int p_size) {
    m_queue_buffer.reserve(p_size);
}
