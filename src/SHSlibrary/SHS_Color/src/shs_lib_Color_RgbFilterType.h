#pragma once

#include <stdint.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            enum class RgbFilterType : uint8_t
            {
                NONE = 0,
                GAMMA = 1,
                COLOR_CORRECTION = 2
            };
        }
    }
}
