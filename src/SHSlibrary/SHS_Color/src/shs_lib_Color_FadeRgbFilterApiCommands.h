#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    enum class FadeRgbEffectApiCommands : uint8_t
    {
        NOCOMMAND = 0,
        ENABLE = 1,
        DISABLE = 2,
        IS_ACTIVE = 3,
        ACTIVE = 4,
        SET_PERIOD = 5,
        GET_PERIOD = 6,
        PERIOD = 7,
        SET_TARGET = 8,
        GET_TARGET = 9,
        TARGET = 10,
    };
}
