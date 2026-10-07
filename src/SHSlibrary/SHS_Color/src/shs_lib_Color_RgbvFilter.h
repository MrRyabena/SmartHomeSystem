#pragma once

#include <shs_Color_RGBV8888.h>


namespace shs::lib::Color
{
    class RgbvFilter;
}

class shs::lib::Color::RgbvFilter
{
public:
    virtual ~RgbvFilter() = default;

    /**
     * @brief Apply the filter to the given color with value channel.
     * @param color The RGBV8888 color to apply the filter to.
     * @return true if the color was changed, false otherwise.
     */
    [[nodiscard]] virtual bool apply(RGBV8888& color) = 0;
};
