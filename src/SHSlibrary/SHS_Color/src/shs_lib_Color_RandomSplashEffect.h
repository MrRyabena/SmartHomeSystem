#pragma once

#include <shs_Random.h>
#include <shs_types.h>

#include <shs_lib_Color_SplashEffect.h>

namespace shs::lib::Color
{
    class RandomSplashEffect;
}

class shs::lib::Color::RandomSplashEffect : public shs::lib::Color::SplashEffect
{
public:
    RandomSplashEffect(const shs::t::shs_time_t min_period, const shs::t::shs_time_t max_period,
        const uint8_t start_brightness = 255,
        const uint8_t min_brightness = 0, const uint8_t max_brightness = 255) noexcept;

    [[nodiscard]] result_t update() override;

protected:
    shs::Random<shs::t::shs_time_t> m_random_period;
};
