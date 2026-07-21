#pragma once

#include <stdint.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            enum class RfbEffectType : uint8_t
            {
                NONE = 0,
                WHEEL1530 = 1,
                FADE = 2,
                PULSE = 3,
                STROBE = 4
            };
        }
    }
}
