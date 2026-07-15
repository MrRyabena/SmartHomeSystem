#pragma once

#include <stdint.h>

#include "shs_lib_Color_RGB888.h"


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct RGBV8888;
        }
    }
}


/**
 * @brief Represents a color in RGB format with an additional value (V) channel, using 8 bits for each channel.
 * The structure inherits from RGB888 and adds a value channel, allowing for representation of colors with
 * an additional intensity, brightness or white component.
 */
struct shs::lib::Color::RGBV8888 : public shs::lib::Color::RGB888
{
    /**
     * @brief Constructs an RGBV8888 color with the specified components.
     * @param red The red component (0-255).
     * @param green The green component (0-255).
     * @param blue The blue component (0-255).
     * @param value The value (intensity/brightness/white) component (0-255).
     */
    explicit RGBV8888(const uint8_t red = 0, const uint8_t green = 0, const uint8_t blue = 0, const uint8_t value = 0xff)
        : RGB888(red, green, blue), value(value)
    {}

    /**
     * @brief Constructs an RGBV8888 color from a 32-bit integer representation.
     * The format is 0xRRGGBBVV, where RR is red, GG is green, BB is blue, and VV is value.
     * @param color The 32-bit integer representing the color.
     */
    explicit RGBV8888(const uint32_t color)
        : RGB888(static_cast<uint32_t>((color >> 16) & 0xFFFF)),
        value(static_cast<uint8_t>(color & 0xFF))
    {}

    /**
     * @brief Constructs an RGBV8888 color from an existing RGB888 color and a value component.
     * @param rgb The RGB888 color to copy the red, green, and blue components from.
     * @param value The value (intensity/brightness/white) component (0-255).
     */
    explicit RGBV8888(const shs::lib::Color::RGB888& rgb, const uint8_t value = 0xff)
        : RGB888(rgb), value(value)
    {}

    /**
     * @brief Converts the RGBV8888 color to a 32-bit integer representation.
     * The format is 0xRRGGBBVV, where RR is red, GG is green, BB is blue, and VV is value.
     * @return The 32-bit integer representing the color.
     */
    operator uint32_t() const
    {
        return (static_cast<uint32_t>(red) << 24) | \
            (static_cast<uint32_t>(green) << 16) | \
            (static_cast<uint32_t>(blue) << 8) | static_cast<uint32_t>(value);
    }

    /**
     * @brief The value (intensity/brightness/white) component (0-255).
     */
    uint8_t value;
};
