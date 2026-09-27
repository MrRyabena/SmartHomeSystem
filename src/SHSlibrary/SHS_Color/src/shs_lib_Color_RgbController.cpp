#include "shs_lib_Color_RgbController.h"

#include "shs_lib_Color_cast.h"

shs::lib::Color::RgbController::RgbController(callback_t callback)
    : m_callback(callback), m_color(0, 0, 0, 0)
{
}

void shs::lib::Color::RgbController::setColor(const RGB888 color)
{
    using namespace shs::lib::Color;

    auto brightness = m_color.value;
    m_color = color_cast<RGBV8888>(color);
    m_color.value = brightness;

    if (m_callback)
    {
        m_callback(m_color);
    }
}
