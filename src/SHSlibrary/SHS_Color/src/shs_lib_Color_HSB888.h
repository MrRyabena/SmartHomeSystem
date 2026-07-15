#pragma once

#include <stdint.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct HSB888;
        }
    }
}

/**
 * @brief Represents a color in HSB format, using 8 bits for each channel.
 * The structure provides constructors for creating colors from individual HSB
 * components or from a 32-bit integer representation.
 */
struct shs::lib::Color::HSB888
{
    explicit HSB888(const uint8_t hue = 0, const uint8_t saturation = 0, const uint8_t brightness = 0)
        : hue(hue), saturation(saturation), brightness(brightness)
    {}

    explicit HSB888(const uint32_t color)
        : hue(static_cast<uint8_t>((color >> 16) & 0xFF)),
        saturation(static_cast<uint8_t>((color >> 8) & 0xFF)),
        brightness(static_cast<uint8_t>(color & 0xFF))
    {}

    operator uint32_t() const
    {
        return (static_cast<uint32_t>(hue) << 16) | \
            (static_cast<uint32_t>(saturation) << 8) | static_cast<uint32_t>(brightness);
    }

    /**
     * @brief The hue component (0-255).
     */
    uint8_t hue;

    /**
     * @brief The saturation component (0-255).
     */
    uint8_t saturation;

    /**
     * @brief The brightness component (0-255).
     */
    uint8_t brightness;
};
