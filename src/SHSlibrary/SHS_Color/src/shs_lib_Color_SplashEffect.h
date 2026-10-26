#pragma once

#include <shs_lib_Color_RgbEffect.h>

namespace shs::lib::Color
{
    class SplashEffect;
}


class shs::lib::Color::SplashEffect : public shs::lib::Color::RgbEffect
{
public:
    SplashEffect(const shs::t::shs_time_t period, const uint8_t start_brightness = 255,
        const uint8_t min_brightness = 0, const uint8_t max_brightness = 255) noexcept;

    [[nodiscard]] result_t update() override;

protected:
    uint8_t m_brightness;
    uint8_t m_min_brightness;
    uint8_t m_max_brightness;

    SplashEffect(const shs::t::shs_time_t period, const uint8_t start_brightness,
        const uint8_t min_brightness, const uint8_t max_brightness,
        const RgbEffectType type) noexcept;
};

