#include "shs_lib_Color_RgbDriver.h"

#if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

#include "shs_lib_Color_RGBV8888.h"


shs::lib::Color::RgbDriver::RgbDriver(const shs::t::shs_pin_t red_pin, const shs::t::shs_pin_t green_pin, const shs::t::shs_pin_t blue_pin,
    const LedType led_type) noexcept
    : m_red(red_pin), m_green(green_pin), m_blue(blue_pin), m_led_type(led_type)
{}

void shs::lib::Color::RgbDriver::start()
{
    m_red.setup();
    m_green.setup();
    m_blue.setup();
}


void shs::lib::Color::RgbDriver::setColor(const RGBV8888& color) noexcept
{
    if (m_led_type == LedType::COMMON_ANODE)
    {
        m_red.on(255 - color.red);
        m_green.on(255 - color.green);
        m_blue.on(255 - color.blue);
    }
    else
    {
        m_red.on(color.red);
        m_green.on(color.green);
        m_blue.on(color.blue);
    }
}


shs::lib::Color::RGB888 shs::lib::Color::RgbDriver::getColor() const noexcept
{
    if (m_led_type == LedType::COMMON_ANODE)
    {
        return shs::lib::Color::RGB888(255 - m_red.getValue(), 255 - m_green.getValue(), 255 - m_blue.getValue());
    }

    return shs::lib::Color::RGB888(m_red.getValue(), m_green.getValue(), m_blue.getValue());
}

#endif    // #if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)
