#include "shs_lib_Color_BrightSmoothFilter.h"

shs::lib::Color::BrightSmoothFilter::BrightSmoothFilter(const shs::t::shs_time_t step_timeout, const uint8_t target_brightness, const uint8_t step)
    : m_step_timer(step_timeout), m_target_brightness(target_brightness), m_step(step)
{}

bool shs::lib::Color::BrightSmoothFilter::apply(uint8_t& value)
{
    if (value == m_target_brightness) return false;

    if (!isEnabled())
    {
        value = m_target_brightness;
        return true;
    }

    if (m_step_timer.check())
    {
        if (value < m_target_brightness)
        {
            value += (value + m_step > m_target_brightness) ? (m_target_brightness - value) : m_step;
        }
        else
        {
            value -= (value - m_step < m_target_brightness) ? (value - m_target_brightness) : m_step;
        }
        return true;
    }

    return false;
}

shs::t::shs_time_t shs::lib::Color::BrightSmoothFilter::calculatePeriod(const uint8_t current_brightness,
    const uint8_t target_brightness, const shs::t::shs_time_t step_timeout, const uint8_t step_size) noexcept
{
    if (current_brightness == target_brightness) return 0;
    if (step_size == 0) return 0;                           // Avoid division by zero
    if (step_timeout == 0) return 0;                        // Avoid division by zero

    const auto brightness_difference = (current_brightness > target_brightness) ?
        (current_brightness - target_brightness) : (target_brightness - current_brightness);

    const auto step_count = (brightness_difference + step_size - 1) / step_size; // Ceiling division to account for any remainder

    return static_cast<shs::t::shs_time_t>(step_timeout * step_count);
}

shs::t::shs_time_t shs::lib::Color::BrightSmoothFilter::calculateStepTimeout(const uint8_t current_brightness,
    const uint8_t target_brightness, const shs::t::shs_time_t period, const uint8_t step_size) noexcept
{
    if (current_brightness == target_brightness) return 0;
    if (step_size == 0) return 0;                           // Avoid division by zero
    if (period == 0) return 0;


    const auto brightness_difference = (current_brightness > target_brightness) ?
        (current_brightness - target_brightness) : (target_brightness - current_brightness);

    const auto step_count = (brightness_difference + step_size - 1) / step_size; // Ceiling division to account for any remainder

    return static_cast<shs::t::shs_time_t>(period / step_count);
}
