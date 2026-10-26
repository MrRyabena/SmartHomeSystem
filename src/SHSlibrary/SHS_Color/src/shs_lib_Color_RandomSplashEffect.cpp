#include "shs_lib_Color_RandomSplashEffect.h"

shs::lib::Color::RandomSplashEffect::RandomSplashEffect(const shs::t::shs_time_t min_period,
    const shs::t::shs_time_t max_period, const uint8_t start_brightness,
    const uint8_t min_brightness, const uint8_t max_brightness) noexcept
    : SplashEffect(min_period, start_brightness, min_brightness, max_brightness, RgbEffectType::RANDOM_SPLASH),
    m_random_period(min_period, max_period)
{
    m_random_period.autoSeed();
}

auto shs::lib::Color::RandomSplashEffect::update() -> result_t
{
    if (m_timer.check())
    {
        m_brightness = (m_brightness == m_min_brightness) ? m_max_brightness : m_min_brightness;
        m_timer.setTimeout(m_random_period.get());
        return result_t{ std::nullopt, m_brightness };
    }

    return result_t{};
}
