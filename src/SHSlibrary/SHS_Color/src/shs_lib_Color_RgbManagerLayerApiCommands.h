#pragma once

#include <stdint.h>


namespace shs::lib::Color
{
    enum class RgbManagerLayerApiCommands : uint8_t
    {
        NOCOMMAND = 0,
        ENABLE_BRIGHT_SMOOTH = 1,
        DISABLE_BRIGHT_SMOOTH = 2,
        SET_BRIGHT_SMOOTH_STEP_TIMEOUT = 3,
        SET_BRIGHT_SMOOTH_STEP = 4,
        ENABLE_FADE = 5,
        DISABLE_FADE = 6,
        SET_FADE_PERIOD = 7,
        PUSH_EFFECT = 8,
        PUSHED_EFFECT_ID = 9,
        POP_EFFECT = 10,
        POPPED_EFFECT_ID = 11,
        REMOVE_EFFECT = 12,
        CLEAR_EFFECTS = 13,
    };
}
