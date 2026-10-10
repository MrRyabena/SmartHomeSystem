#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    enum class BrightSmoothFilterApiCommands : uint8_t
    {
        NOCOMMAND = 0,
        ENABLE = 1,
        DISABLE = 2,
        IS_ENABLED = 3,
        ENABLED = 4,
        SET_STEP_TIMEOUT = 5,
        GET_STEP_TIMEOUT = 6,
        STEP_TIMEOUT = 7,
        SET_STEP = 8,
        GET_STEP = 9,
        STEP = 10,
        SET_TARGET = 11,
        GET_TARGET = 12,
        TARGET = 13,
    };
}
