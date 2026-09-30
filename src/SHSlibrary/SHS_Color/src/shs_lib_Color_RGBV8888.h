#pragma once

#include <stdint.h>

#include "shs_lib_Color_RGB888.h"


namespace shs::lib::Color
{
    struct RGBV8888;
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
     * @brief Assigns the values of an RGB888 color to the RGBV8888 color.
     * @param rgb The RGB888 color to copy the red, green, and blue components from.
     * @return A reference to the assigned RGBV8888 color.
     * @note The value component of the RGBV8888 color remains unchanged during this assignment.
     */
    RGBV8888& operator=(const shs::lib::Color::RGB888& rgb)
    {
        if (this == &rgb) return *this;  // Self-assignment check

        setRgb(rgb);  // Copy RGB components from the RGB888 color

        return *this;
    }

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
     * @brief Applies the value component to the RGB components, effectively adjusting their brightness.
     * This method modifies the red, green, and blue components based on the value component.
     * If the value is 255, the RGB components remain unchanged. Otherwise, each RGB component
     * is scaled down proportionally to the value, resulting in a dimmer color.
     * @note The value component will be set to 255 after applying the brightness.
     */
    void applyBrightness()
    {
        if (value == 255) return;

        red = static_cast<uint8_t>((static_cast<uint16_t>(red) * (value + 1)) >> 8);
        green = static_cast<uint8_t>((static_cast<uint16_t>(green) * (value + 1)) >> 8);
        blue = static_cast<uint8_t>((static_cast<uint16_t>(blue) * (value + 1)) >> 8);

        value = 255;
    }

    RGB888 getNormalized() const
    {
        RGB888 normalized_color(red, green, blue);
        normalized_color.red = static_cast<uint8_t>((static_cast<uint16_t>(normalized_color.red) * (value + 1)) >> 8);
        normalized_color.green = static_cast<uint8_t>((static_cast<uint16_t>(normalized_color.green) * (value + 1)) >> 8);
        normalized_color.blue = static_cast<uint8_t>((static_cast<uint16_t>(normalized_color.blue) * (value + 1)) >> 8);

        return normalized_color;
    }

    /**
     * @brief Sets the RGB components of the color.
     * @param rgb The RGB color to copy the red, green, and blue components from.
     */
    void setRgb(const RGB888& rgb)
    {
        red = rgb.red;
        green = rgb.green;
        blue = rgb.blue;
    }

    /**
     * @brief Retrieves the RGB components of the color as an RGB888 structure.
     * @return An RGB888 structure containing the red, green, and blue components.
     */
    RGB888 getRgb() const
    {
        return RGB888{ red, green, blue };
    }

    /**
     * @brief The value (intensity/brightness/white) component (0-255).
     */
    uint8_t value;
};
