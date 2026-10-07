#include "shs_lib_Color_RgbManagerLayer.h"


shs::lib::Color::RgbManagerLayer::RgbManagerLayer(RGBV8888 base_color, std::vector<std::unique_ptr<RgbEffect>> effects)
    : m_effects(std::move(effects)), m_color(base_color), m_fade_filter(FadeRgbFilter::FADER_MIN_PERIOD), m_brightness_filter(BrightSmoothFilter(100, 255, 1)), m_active(true)
{}

shs::lib::Color::RgbManagerLayer::RgbManagerLayer(BrightSmoothFilter bright_filter, FadeRgbFilter fade_filter, RGBV8888 base_color, std::vector<std::unique_ptr<RgbEffect>> effects)
    : m_effects(std::move(effects)), m_color(base_color), m_fade_filter(std::move(fade_filter)), m_brightness_filter(std::move(bright_filter)), m_active(true)
{}

bool shs::lib::Color::RgbManagerLayer::apply(RGBV8888& color)
{
    if (!m_active) return false;

    bool result = false;

    for (auto& effect : m_effects)
    {
        auto value = effect->getColor();
        if (value.first)
        {
            setColor(*value.first);
            result = true;
        }
        if (value.second)
        {
            setBrightness(*value.second);
            result = true;
        }
    }

    if (m_brightness_filter.isEnabled())
    {
        result += m_brightness_filter.apply(color.value);
        m_color.value = color.value;
    }
    if (m_fade_filter.isActive())
    {
        result += m_fade_filter.apply(color);
        m_color.setRgb(color);
    }

    return result;
}

void shs::lib::Color::RgbManagerLayer::setColor(const RGB888 color)
{
    m_fade_filter.setTarget(color);
}

void shs::lib::Color::RgbManagerLayer::setBrightness(const uint8_t brightness)
{
    m_brightness_filter.setTarget(brightness);
}
