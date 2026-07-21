#pragma once


#include <stdint.h>
#include <shs_algorithm.h>
#include <assert.h>


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct Kelvin;
        }
    }
}


/**
 * @brief Represents a color in Kelvin format, using a 16-bit unsigned integer to represent the color temperature in Kelvin.
 * The structure provides constructors for creating colors from a Kelvin value or from a 32-bit integer representation.
 */
struct shs::lib::Color::Kelvin
{
    /**
     * @brief Constructs a Kelvin color with the specified color temperature.
     * @param temp_kelvin The color temperature in Kelvin (1000-10000).
     * @note The constructor clamps the input value to the range of 1000 to 10000 Kelvin.
     */
    constexpr explicit Kelvin(const uint16_t temp_kelvin) noexcept
        : kelvin(shs::clamp(temp_kelvin, static_cast<uint16_t>(1000), static_cast<uint16_t>(10000)))
    {}

    uint16_t kelvin; /**< The color temperature in Kelvin (1000-10000). */
};
