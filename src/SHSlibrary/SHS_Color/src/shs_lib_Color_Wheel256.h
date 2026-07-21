#pragma once

#include <stdint.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct Wheel256;
        }
    }
}

/**
 * @brief Represents a color in Wheel format, using 8 bits for the wheel channel.
 * The structure provides constructors for creating colors from a wheel value or from a 32-bit integer representation.
 */
struct shs::lib::Color::Wheel256
{
    explicit Wheel256(const uint8_t wheel = 0)
        : wheel(wheel)
    {}

    uint8_t wheel; /**< The wheel component (0-255). */
};
