#pragma once

#include <shs_settings_private.h>

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <FastLED.h>

#include <shs_lib_Color_RgbController.h>
#include <shs_lib_Color_RGB888.h>
#include <shs_lib_Color_RGBV8888.h>

namespace shs::argb
{
    class ColorController;
}


class shs::argb::ColorController : public shs::lib::Color::RgbController
{
public:
    ColorController(CLEDController* controller) noexcept : m_controller(controller) {}

    void setColor(const RGB888 color) override
    {
        m_color.setRgb(color);
        show();
    }
    [[nodiscard]] RGB888 getColor() const noexcept override { return m_color.getRgb(); }

    void setBrightness(const uint8_t brightness) override
    {
        m_color.value = brightness;
        show();
    }
    [[nodiscard]] uint8_t getBrightness() const noexcept override { return m_color.value; }

    void setValue(const RGBV8888 color) override
    {
        m_color = color;
        show();
    }
    [[nodiscard]] RGBV8888 getValue() const noexcept override { return m_color; }

protected:
    CLEDController* m_controller;
    RGBV8888 m_color;

    void show() noexcept
    {
        if (!m_controller) return;
        auto color = m_color.getNormalized();
        m_controller->showColor(color.red, color.green, m_color.blue);
    }
};


#endif  // #ifndef SHS_LIB_ARGB_NO_FASTLED
