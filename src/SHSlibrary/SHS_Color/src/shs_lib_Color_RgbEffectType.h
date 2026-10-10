#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    enum class RgbEffectType : uint8_t
    {
        UNKNOWN = 0,
        WHEEL1530 = 1,
        FADE = 2,
        PULSE = 3,
        STROBE = 4,
        FIRE = 5,
    };
}
