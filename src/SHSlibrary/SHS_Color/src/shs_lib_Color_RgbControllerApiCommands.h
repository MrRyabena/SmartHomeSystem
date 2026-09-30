#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    enum class RgbControllerApiCommands : uint8_t
    {
        NO_COMMAND = 0,
        SET_COLOR = 1,
        GET_COLOR = 2,
        COLOR = 3,
        SET_BRIGHTNESS = 4,
        GET_BRIGHTNESS = 5,
        BRIGHTNESS = 6,
    };
}
