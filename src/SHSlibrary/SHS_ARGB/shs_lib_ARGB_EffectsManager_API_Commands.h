#pragma once

#include <stdint.h>

namespace shs
{
    namespace argb
    {
        enum class EffectsManager_API_Commands : uint8_t
        {
            NO_COMMAND = 0,
            RESET_EFFECTS = 1,
            SET_RANDOM_MATRIX = 2,
        };
    }
}
