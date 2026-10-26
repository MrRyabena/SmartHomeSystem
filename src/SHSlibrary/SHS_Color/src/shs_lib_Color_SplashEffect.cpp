#include "shs_lib_Color_SplashEffect.h"

shs::lib::Color::SplashEffect::SplashEffect(const shs::t::shs_time_t period, const uint8_t start_brightness,
    const uint8_t min_brightness, const uint8_t max_brightness) noexcept
    : SplashEffect(period, start_brightness, min_brightness, max_brightness, RgbEffectType::SPLASH)
{}

shs::lib::Color::SplashEffect::SplashEffect(const shs::t::shs_time_t period, const uint8_t start_brightness,
    const uint8_t min_brightness, const uint8_t max_brightness, const RgbEffectType type) noexcept
    : shs::lib::Color::RgbEffect(period, type), m_brightness(start_brightness),
    m_min_brightness(min_brightness), m_max_brightness(max_brightness)
{}

auto shs::lib::Color::SplashEffect::update() -> result_t
{
    if (m_timer.check())
    {
        m_brightness = (m_brightness == m_min_brightness) ? m_max_brightness : m_min_brightness;
        return result_t{ std::nullopt, m_brightness };
    }

    return result_t{};
}
