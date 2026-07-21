#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <shs_Process.h>

#include "shs_lib_Color_RGBV8888.h"

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            class RgbFilter;
            class RgbController;
        }
    }
}


class shs::lib::Color::RgbController : public shs::Process
{
public:
    using callback_t = std::function<void(const RGBV8888&)>;

    RgbController(callback_t callback = nullptr);
    ~RgbController() override = default;

    void setColor(const RGBV8888 color);
    RGBV8888 getColor() const noexcept { return m_color; }
    

    void setBrightness(const uint8_t brightness) noexcept { m_color.value = brightness; }



private:
    callback_t m_callback;
    RGBV8888 m_color;

};
