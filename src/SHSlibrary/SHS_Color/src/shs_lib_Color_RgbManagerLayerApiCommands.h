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
        POP_EFFECT = 6,
        EFFECT_PUSHED_ID = 7,
        REMOVE_EFFECT = 8,
        CLEAR_EFFECTS = 9,
        
    };
}
