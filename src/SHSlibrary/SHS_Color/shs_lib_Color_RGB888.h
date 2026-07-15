#pragma once

#include <stdint.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct RGB888;
        }
    }
}


/**
 * @brief Represents a color in RGB format, using 8 bits for each channel.
 * The structure provides constructors for creating colors from individual RGB
 * components or from a 32-bit integer representation.
 */
struct shs::lib::Color::RGB888
{
    /**
     * @brief Constructs an RGB888 color with the specified components.
     * @param red The red component (0-255).
     * @param green The green component (0-255).
     * @param blue The blue component (0-255).
     */
    explicit RGB888(const uint8_t red = 0, const uint8_t green = 0, const uint8_t blue = 0)
        : red(red), green(green), blue(blue)
    {}

    /**
     * @brief Constructs an RGB888 color from a 32-bit integer representation.
     * The format is 0xRRGGBB, where RR is red, GG is green, and BB is blue.
     * @param color The 32-bit integer representing the color.
     */
    explicit RGB888(const uint32_t color)
        : red(static_cast<uint8_t>((color >> 16) & 0xFF)),
        green(static_cast<uint8_t>((color >> 8) & 0xFF)),
        blue(static_cast<uint8_t>(color & 0xFF))
    {}

    /**
     * @brief Converts the RGB888 color to a 32-bit integer representation.
     * The format is 0xRRGGBB, where RR is red, GG is green, and BB is blue.
     * @return The 32-bit integer representing the color.
     */
    operator uint32_t() const
    {
        return (static_cast<uint32_t>(red) << 16) | \
            (static_cast<uint32_t>(green) << 8) | static_cast<uint32_t>(blue);
    }

    /**
     * @brief The red component (0-255).
     */
    uint8_t red;

    /**
     * @brief The green component (0-255).
     */
    uint8_t green;

    /**
     * @brief The blue component (0-255).
     */
    uint8_t blue;
};
