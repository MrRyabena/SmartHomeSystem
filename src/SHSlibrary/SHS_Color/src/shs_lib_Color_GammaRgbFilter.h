#pragma once


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct RGB888;
            class RgbFilter;
            class GammaRgbFilter;
        }
    }
}


class shs::lib::Color::GammaRgbFilter : public shs::lib::Color::RgbFilter
{
public:
    GammaRgbFilter();
    ~GammaRgbFilter() override = default;


    void apply(Color::RGB888& color);

private:


};
