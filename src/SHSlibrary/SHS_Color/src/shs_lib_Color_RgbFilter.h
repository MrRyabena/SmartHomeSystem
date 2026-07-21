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

    virtual void apply(shs::lib::Color::RGB888& color) = 0;

};
