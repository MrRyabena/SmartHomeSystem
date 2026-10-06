#include "shs_lib_Color_FadeRgbFilter.h"

#include <shs_lib_Color_cast.h>

shs::lib::Color::FadeRgbFilter::FadeRgbFilter(const shs::t::shs_time_t period)
    : m_timer(shs::ProgramTimer::MAX_TIMEOUT), m_period(period), m_target_color(RGB888(0, 0, 0)),
    m_start_color(RGB888(0, 0, 0)), m_step(0), m_n(0)
{}

void shs::lib::Color::FadeRgbFilter::setTarget(const RGB888 target_color)
{
    m_target_color = target_color;

    m_resetRunning();
}

void shs::lib::Color::FadeRgbFilter::setPeriod(shs::t::shs_time_t period) noexcept
{
    m_period = period;

    m_resetRunning();
}

bool shs::lib::Color::FadeRgbFilter::apply(RGB888& color)
{
    if (!isActive()) return false;

    if (!m_isRunning())
    {
        m_start_color = color;
        m_prepare();
    }

    if (m_timer.check())
    {
        if (m_step + 1 == (1 << m_n))
        {
            color = m_target_color;
            m_resetRunning();
            return true;
        }
        ++m_step;

        color.red = m_target_color.red + (((static_cast<int32_t>(m_target_color.red) - m_start_color.red) * m_step) >> m_n);
        color.green = m_target_color.green + (((static_cast<int32_t>(m_target_color.green) - m_start_color.green) * m_step) >> m_n);
        color.blue = m_target_color.blue + (((static_cast<int32_t>(m_target_color.blue) - m_start_color.blue) * m_step) >> m_n);

        return true;
    }

    return false;
}

void shs::lib::Color::FadeRgbFilter::m_prepare()
{
    auto diff = [](uint8_t a, uint8_t b) -> uint8_t { return a > b ? a - b : b - a; };
    auto max3 = [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c); };

    uint8_t steps = max3(diff(m_start_color.red, m_target_color.red), diff(m_start_color.green, m_target_color.green), diff(m_start_color.blue, m_target_color.blue));

    if (steps == 0)
    {
        m_resetRunning();
        return;
    }


    m_timer.setTimeout((m_period + steps - 1) / steps);

    if (m_timer.getTimeout() < FADER_MIN_PERIOD)
    {
        steps = m_period / m_timer.getTimeout();
        m_timer.setTimeout(FADER_MIN_PERIOD);
    }

    m_step = 0;
    m_n = 0;
    while (steps)
    {
        ++m_n;
        steps >>= 1;
    }

    m_timer.setTimeout(m_period / (1 << m_n));
}
