#include "shs_lib_Color_RgbController.h"

shs::lib::Color::RgbController::RgbController(callback_t callback)
    : m_callback(callback), m_color(0, 0, 0, 0)
{}

void shs::lib::Color::RgbController::setColor(const RGBV8888 color)
{
    auto brightness = m_color.value;
    m_color = color;
    m_color.applyBrightness();
    m_color.value = brightness;  // Preserve the original brightness value

    if (m_callback)
    {
        m_callback(m_color);
    }
}
