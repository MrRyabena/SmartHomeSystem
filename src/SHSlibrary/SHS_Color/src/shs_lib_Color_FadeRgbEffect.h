#pragma once

#include "shs_lib_Color_RgbEffect.h"
#include "shs_lib_Color_RGB888.h"


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            class FadeRgbEffect;
        }
    }
}


class shs::lib::Color::FadeRgbEffect : public shs::lib::Color::RgbEffect
{
public:

    static constexpr auto FADER_MIN_PERIOD = 20u;  // Minimum period for the fade effect in milliseconds

    FadeRgbEffect(const shs::t::shs_time_t period, callback_t callback, const RGB888& start_color = RGB888{}, const RGB888& end_color = RGB888{});

    void setTargetColor(const RGB888& target_color, const RGB888& current_color);
    void setPeriod(shs::t::shs_time_t period) noexcept override;
    shs::t::shs_time_t getPeriod() const noexcept override;

    void enable() noexcept { m_active = true; }
    void disable() noexcept { m_active = false; }
    bool isActive() const noexcept { return m_active; }

    void start() override {}
    void tick() override;
    void stop() override {}

protected:
    RGB888 m_color;
    RGB888 m_target_color;
    shs::t::shs_time_t m_period;
    uint8_t m_step;
    uint8_t m_n;
    bool m_active;

    void m_update();
};
