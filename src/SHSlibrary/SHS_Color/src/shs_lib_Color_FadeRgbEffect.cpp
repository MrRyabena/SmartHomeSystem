#include "shs_lib_Color_FadeRgbEffect.h"

#include <shs_lib_Color_cast.h>

shs::lib::Color::FadeRgbEffect::FadeRgbEffect(const shs::t::shs_time_t period, callback_t callback, const RGB888& start_color, const RGB888& end_color)
    : m_color(start_color), m_target_color(end_color), m_period(period), RgbEffect(period, callback), m_active(true), m_step(0)
{
    m_update();
}

void shs::lib::Color::FadeRgbEffect::setTargetColor(const RGB888& target_color, const RGB888& current_color)
{
    if (m_active && m_callback) callback(color_cast<RGBV8888>(m_color));

    m_target_color = target_color;
    m_color = current_color;

    m_update();
}

void shs::lib::Color::FadeRgbEffect::setPeriod(shs::t::shs_time_t period) noexcept
{
    m_period = period;
    m_update();
}

shs::t::shs_time_t shs::lib::Color::FadeRgbEffect::getPeriod() const noexcept
{
    return m_period;
}

void shs::lib::Color::FadeRgbEffect::tick()
{
    if (!m_active) return;

    if (m_timer.check())
    {
        if (m_step + 1 == (1 << m_n))
        {
            m_timer.setTimeout(0);
            if (m_callback) m_callback(color_cast<RGBV8888>(m_target_color));
            return;
        }
        ++m_step;

        m_color = RGB888(
            m_target_color.red + (((static_cast<int32_t>(m_target_color.red) - m_color.red) * m_step) >> m_n),
            m_target_color.green + (((static_cast<int32_t>(m_target_color.green) - m_color.green) * m_step) >> m_n),
            m_target_color.blue + (((static_cast<int32_t>(m_target_color.blue) - m_color.blue) * m_step) >> m_n)
        );

        if (m_callback) m_callback(color_cast<RGBV8888>(m_color));
    }
}

void shs::lib::Color::FadeRgbEffect::m_update()
{
    auto diff = [](uint8_t a, uint8_t b) -> uint8_t { return a > b ? a - b : b - a; };
    auto max3 = [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c); };

    uint8_t steps = max3(diff(m_color.red, m_target_color.red), diff(m_color.green, m_target_color.green), diff(m_color.blue, m_target_color.blue));

    if (!steps)
    {
        m_timer.setTimeout(0);
        m_active = false;
        return;
    }

    m_timer.setTimeout((m_period + steps - 1) / steps);

    if (m_timer.getTimeout() < FADER_MIN_PERIOD)
    {
        steps = m_period / m_timer.getTimeout();
        m_timer.setTimeout(FADER_MIN_PERIOD);
    }

    m_n = 0;
    while (steps)
    {
        ++m_n;
        steps >>= 1;
    }

    m_timer.setTimeout(m_period / (1 << m_n));
}



