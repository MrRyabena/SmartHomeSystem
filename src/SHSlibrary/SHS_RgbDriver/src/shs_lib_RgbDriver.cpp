#include "shs_lib_RgbDriver.h"

#if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

#include "shs_lib_Color_RGBV8888.h"


shs::lib::Color::RgbDriver::RgbDriver(const shs::t::shs_pin_t red_pin, const shs::t::shs_pin_t green_pin, const shs::t::shs_pin_t blue_pin,
    const LedType led_type) noexcept
    : m_red(red_pin), m_green(green_pin), m_blue(blue_pin), m_led_type(led_type), m_color(0, 0, 0, 255)
{}

void shs::lib::Color::RgbDriver::setup()
{
    m_red.setup();
    m_green.setup();
    m_blue.setup();
}


void shs::lib::Color::RgbDriver::setColor(const RGB888 color)
{
    m_color.setRgb(color);

    m_show();
}


shs::lib::Color::RGB888 shs::lib::Color::RgbDriver::getColor() const
{
    return m_color.getRgb();
}

void shs::lib::Color::RgbDriver::setBrightness(const uint8_t brightness)
{
    m_color.value = brightness;
    
    m_show();
}

void shs::lib::Color::RgbDriver::setValue(const RGBV8888 color)
{
    m_color = color;

    m_show();
}

void shs::lib::Color::RgbDriver::m_show()
{
    auto output = m_color.getNormalized();

    if (m_led_type == LedType::COMMON_ANODE)
    {
        m_red.on(255 - output.red);
        m_green.on(255 - output.green);
        m_blue.on(255 - output.blue);
    }
    else
    {
        m_red.on(output.red);
        m_green.on(output.green);
        m_blue.on(output.blue);
    }
}

#endif    // #if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)
