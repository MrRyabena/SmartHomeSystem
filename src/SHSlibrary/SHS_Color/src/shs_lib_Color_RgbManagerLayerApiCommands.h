#pragma once

#include <stdint.h>


namespace shs::lib::Color
{
    enum class RgbManagerLayerApiCommand : uint8_t
    {
        NOCOMMAND = 0,
        ENABLE_BRIGHT_SMOOTH = 1,
        DISABLE_BRIGHT_SMOOTH = 2,
        ENABLE_FADE = 3,
        DISABLE_FADE = 4,
        PUSH_EFFECT = 5,
        PUSHED_EFFECT_ID = 7,
        POP_EFFECT = 6,
        POPPED_EFFECT_ID = 8,
        REMOVE_EFFECT = 9,
        CLEAR_EFFECTS = 10,
    };
}
