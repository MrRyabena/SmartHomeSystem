#pragma once

#include "shs_lib_Color_RgbFilter.h"

namespace shs::lib::Color
{
    struct RGB888;
    class RgbFilter;
    class GammaRgbFilter;
}


class shs::lib::Color::GammaRgbFilter : public shs::lib::Color::RgbFilter
{
public:
    GammaRgbFilter();
    ~GammaRgbFilter() override = default;


    bool apply(Color::RGB888& color);

private:
};
