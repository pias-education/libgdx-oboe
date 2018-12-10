#pragma once

#include <cstdint>

/// Interface for writing audio into raw audio stream
class renderable_audio {
    public:
        virtual void render(int16_t*, int32_t) const = 0;
        virtual bool is_done() const = 0;
        virtual ~renderable_audio() = default;
};