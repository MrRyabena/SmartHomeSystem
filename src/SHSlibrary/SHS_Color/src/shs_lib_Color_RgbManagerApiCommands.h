#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    enum class RgbManagerApiCommands : uint8_t
    {
        NOCOMMAND = 0,
        ADD_LAYER = 1,
        LAYER_ADDED_ID = 2,
        REMOVE_LAYER = 3,
        POP_LAYER = 4,
        LAYER_POPPED_ID = 5,
        CLEAR_LAYERS = 6,
        MANAGE_LAYER = 7,
        MANAGE_CONTROLLER = 8,
    };
}
