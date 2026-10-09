#include "shs_lib_RgbDriver.h"

#if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

#include "shs_lib_Color_RGBV8888.h"


shs::lib::Color::RgbDriver::RgbDriver(const shs::t::shs_pin_t red_pin, const shs::t::shs_pin_t green_pin, const shs::t::shs_pin_t blue_pin,
    const LedType led_type) noexcept
    : m_red(red_pin), m_green(green_pin), m_blue(blue_pin), m_led_type(led_type), m_brightness(0)
{}

void shs::lib::Color::RgbDriver::setup()
{
    m_red.setup();
    m_green.setup();
    m_blue.setup();
}


void shs::lib::Color::RgbDriver::setColor(const RGB888 color)
{
    RGBV8888 color_with_brightness(color, m_brightness);

    auto output = color_with_brightness.getNormalized();

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


shs::lib::Color::RGB888 shs::lib::Color::RgbDriver::getColor() const
{
    if (m_led_type == LedType::COMMON_ANODE)
    {
        return shs::lib::Color::RGB888(255 - m_red.getValue(), 255 - m_green.getValue(), 255 - m_blue.getValue());
    }

    return shs::lib::Color::RGB888(m_red.getValue(), m_green.getValue(), m_blue.getValue());
}

void shs::lib::Color::RgbDriver::setBrightness(const uint8_t brightness)
{
    auto current_color = getColor();
    current_color.red = (static_cast<uint16_t>(current_color.red) * m_brightness) / 255;
    current_color.green = (static_cast<uint16_t>(current_color.green) * m_brightness) / 255;
    current_color.blue = (static_cast<uint16_t>(current_color.blue) * m_brightness) / 255;

    m_brightness = brightness;
    setColor(current_color);
}

shs::lib::Color::RGBV8888 shs::lib::Color::RgbDriver::getValue() const
{
    if (m_led_type == LedType::COMMON_ANODE)
    {
        return RGBV8888(255 - m_red.getValue(), 255 - m_green.getValue(), 255 - m_blue.getValue(), m_brightness);
    }
    return RGBV8888(m_red.getValue(), m_green.getValue(), m_blue.getValue(), m_brightness);
}

#endif    // #if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)
