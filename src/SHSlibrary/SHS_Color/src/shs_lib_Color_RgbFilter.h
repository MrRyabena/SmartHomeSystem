#pragma once


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct RGB888;
            class RgbFilter;
        }
    }
}


class shs::lib::Color::RgbFilter
{
public:
    virtual ~RgbFilter() = default;

    /**
     * @brief Apply the filter to the given color.
     * @param color The color to apply the filter to.
     * @return true if the color was changed, false otherwise.
     */
    [[nodiscard]] virtual bool apply(shs::lib::Color::RGB888& color) = 0;

};
