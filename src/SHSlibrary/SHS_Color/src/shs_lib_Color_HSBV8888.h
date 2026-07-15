#pragma once

#include <stdint.h>
#include "shs_lib_Color_HSB888.h"

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct HSBV8888;
        }
    }
}

/**
 * @brief Represents a color in HSB format with an additional value (V) channel, using 8 bits for each channel.
 * The structure inherits from HSB888 and adds a value channel, allowing for representation of colors with
 * an additional intensity, brightness or white component.
 */
struct shs::lib::Color::HSBV8888 : public shs::lib::Color::HSB888
{
    /**
     * @brief Constructs an HSBV8888 color with the specified components.
     * @param hue The hue component (0-255).
     * @param saturation The saturation component (0-255).
     * @param brightness The brightness component (0-255).
     * @param value The value (intensity/brightness/white) component (0-255).
     */
    explicit HSBV8888(const uint8_t hue = 0, const uint8_t saturation = 0, const uint8_t brightness = 0, const uint8_t value = 0xff)
        : HSB888(hue, saturation, brightness), value(value)
    {}

    /**
     * @brief Constructs an HSBV8888 color from a 32-bit integer representation.
     * The format is 0xHHSSBBVV, where HH is hue, SS is saturation, BB is brightness, and VV is value.
     * @param color The 32-bit integer representing the color.
     */
    explicit HSBV8888(const uint32_t color)
        : HSB888(static_cast<uint32_t>((color >> 16) & 0xFFFFFF)),
        value(static_cast<uint8_t>(color & 0xFF))
    {}

    /**
     * @brief Constructs an HSBV8888 color from an existing HSB888 color and a value component.
     * @param hsb The HSB888 color to copy the hue, saturation, and brightness components from.
     * @param value The value (intensity/brightness/white) component (0-255).
     */
    explicit HSBV8888(const shs::lib::Color::HSB888& hsb, const uint8_t value = 0xff)
        : HSB888(hsb), value(value)
    {}

    /**
     * @brief Converts the HSBV8888 color to a 32-bit integer representation.
     * The format is 0xHHSSBBVV, where HH is hue, SS is saturation, BB is brightness, and VV is value.
     * @return The 32-bit integer representing the color.
     */
    operator uint32_t() const
    {
        return (static_cast<uint32_t>(hue) << 24) | \
            (static_cast<uint32_t>(saturation) << 16) | \
            (static_cast<uint32_t>(brightness) << 8) | static_cast<uint32_t>(value);
    }

    /**
     * @brief The value (intensity/brightness/white) component (0-255).
     */
    uint8_t value;
};
