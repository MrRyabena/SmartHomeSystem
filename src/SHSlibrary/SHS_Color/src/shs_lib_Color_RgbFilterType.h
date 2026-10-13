#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    enum class RgbFilterType : uint8_t
    {
        NONE = 0,
        GAMMA = 1,
        COLOR_CORRECTION = 2,
        BRIGHT_SMOOTH = 3,
        FADE_RGB = 4,
    };
}
