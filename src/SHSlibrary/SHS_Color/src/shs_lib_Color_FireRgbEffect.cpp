#include "shs_lib_Color_FireRgbEffect.h"

#include <algorithm.h>

#include "shs_lib_Color_HSB888.h"
#include "shs_lib_Color_cast.h"


shs::lib::Color::FireRgbEffect::FireRgbEffect(uint8_t start_hue, uint8_t hue_gap,
    shs::t::shs_float_t smooth_k, shs::t::shs_time_t duration,
    uint8_t min_brightness, uint8_t max_brightness,
    uint8_t min_saturation, uint8_t max_saturation)
    : RgbEffect(duration), m_random(2, 10), m_smooth_k(smooth_k),
    m_fire_value(0.0f), m_fire_rnd(0), m_timeout_counter(0),
    m_start_hue(start_hue), m_hue_gap(hue_gap),
    m_min_brightness(min_brightness), m_max_brightness(max_brightness),
    m_min_saturation(min_saturation), m_max_saturation(max_saturation),
{}

result_t shs::lib::Color::FireRgbEffect::update()
{
    if (m_fire_timer.check())
    {
        if (++m_timeout_counter >= 5)
        {
            m_fire_rnd = m_random.get();
            m_timeout_counter = 0;
        }

        m_fire_value = static_cast<shs::t::shs_float_t>(m_fire_value) * (1 - m_smooth_k) + static_cast<shs::t::shs_float_t>(m_fire_rnd) * 10 * m_smooth_k;

        HSB888 hsb(std::clamp(map(m_fire_value, 20, 60, m_start_hue, m_start_hue + m_hue_gap), 0, 255),
            std::clamp(map(m_fire_value, 20, 60, m_max_saturation, m_min_saturation), 0, 255),
            std::clamp(map(m_fire_value, 20, 60, m_min_brightness, m_max_brightness), 0, 255)
        );

        using shs::lib::Color::color_cast;
        return { color_cast<RGB888>(hsb), std::nullopt };
    }

    return { std::nullopt, std::nullopt };
}

void shs::lib::Color::FireRgbEffect::setPeriod(const shs::t::shs_time_t period) noexcept
{
    m_timer.setTimeout(period);
    m_timer.reset();
}

shs::t::shs_time_t shs::lib::Color::FireRgbEffect::getPeriod() const noexcept
{
    return m_timer.getTimeout();
}
