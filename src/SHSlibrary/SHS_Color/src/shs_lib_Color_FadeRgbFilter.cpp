#include "shs_lib_Color_FadeRgbFilter.h"

#include <shs_lib_Color_cast.h>

shs::lib::Color::FadeRgbFilter::FadeRgbFilter(const shs::t::shs_time_t period)
    : m_timer(shs::ProgramTimer::MAX_TIMEOUT), m_period(period), m_target_color(RGB888(0, 0, 0)),
    m_start_color(RGB888(0, 0, 0)), m_step(shs::ProgramTimer::MAX_TIMEOUT), m_steps(0)
{}

void shs::lib::Color::FadeRgbFilter::setTarget(const RGB888 target_color)
{
    m_target_color = target_color;

    m_resetRunning();
}

void shs::lib::Color::FadeRgbFilter::setPeriod(const shs::t::shs_time_t period) noexcept
{
    m_period = period;

    m_resetRunning();
}

bool shs::lib::Color::FadeRgbFilter::apply(RGB888& color)
{
    if (!isActive())
    {
        if (color != m_target_color)
        {
            color = m_target_color;
            return true;
        }
        return false;
    }

    if (!m_isRunning())
    {
        m_start_color = color;
        if (!m_prepare()) return false;
    }

    if (m_timer.check())
    {
        ++m_step;

        if (m_step >= m_steps)
        {
            color = m_target_color;
            m_resetRunning();
            return true;
        }

  color.red = static_cast<uint8_t>(static_cast<int32_t>(m_start_color.red) +
            (static_cast<int32_t>(m_target_color.red) - m_start_color.red) *
            static_cast<int32_t>(m_step) / static_cast<int32_t>(m_steps));
        color.green = static_cast<uint8_t>(static_cast<int32_t>(m_start_color.green) +
            (static_cast<int32_t>(m_target_color.green) - m_start_color.green) *
            static_cast<int32_t>(m_step) / static_cast<int32_t>(m_steps));
        color.blue = static_cast<uint8_t>(static_cast<int32_t>(m_start_color.blue) +
            (static_cast<int32_t>(m_target_color.blue) - m_start_color.blue) *
            static_cast<int32_t>(m_step) / static_cast<int32_t>(m_steps));

        return true;
    }

    return false;
}

bool shs::lib::Color::FadeRgbFilter::m_prepare()
{
    auto diff = [](uint8_t a, uint8_t b) -> uint8_t { return a > b ? a - b : b - a; };
    auto max3 = [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c); };

    const auto color_steps = max3(diff(m_start_color.red, m_target_color.red), diff(m_start_color.green, m_target_color.green), diff(m_start_color.blue, m_target_color.blue));

    if (color_steps == 0)
    {
        m_steps = 0;
        m_resetRunning();
        return false;
    }

    const auto effective_period = m_period < FADER_MIN_PERIOD ? FADER_MIN_PERIOD : m_period;
    const auto max_steps = effective_period / FADER_MIN_PERIOD;
    m_steps = color_steps < max_steps ? color_steps : max_steps;
    if (m_steps == 0) m_steps = 1;

    m_timer.setTimeout(effective_period / m_steps);
    m_timer.reset();
    m_step = 0;
    return true;
}
