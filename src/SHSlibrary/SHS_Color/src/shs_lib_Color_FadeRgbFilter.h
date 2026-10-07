#pragma once

#include <shs_ProgramTimer.h>
#include <shs_types.h>

#include "shs_lib_Color_RgbFilter.h"
#include "shs_lib_Color_RGB888.h"


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            class FadeRgbFilter;
        }
    }
}


class shs::lib::Color::FadeRgbFilter : public shs::lib::Color::RgbFilter
{
public:

    static constexpr auto FADER_MIN_PERIOD = 20u;  // Minimum period for the fade effect in milliseconds

    FadeRgbFilter(const shs::t::shs_time_t period);

    [[nodiscard]] bool apply(RGB888& color) override;

    void setTarget(const RGB888 target_color);
    [[nodiscard]] RGB888 getTarget() const noexcept { return m_target_color; }

    void setPeriod(const shs::t::shs_time_t period) noexcept;
    [[nodiscard]] shs::t::shs_time_t getPeriod() const noexcept { return m_period; }


    void enable() noexcept { m_timer.setTimeout(0); }
    void disable() noexcept { m_timer.setTimeout(shs::ProgramTimer::MAX_TIMEOUT); }
    bool isActive() const noexcept { return m_timer.getTimeout() != shs::ProgramTimer::MAX_TIMEOUT; }

protected:
    shs::ProgramTimer m_timer;
    shs::t::shs_time_t m_period;
    RGB888 m_target_color;
    RGB888 m_start_color;
    uint8_t m_step;
    uint8_t m_n;

    void m_prepare();
    bool m_isRunning() const noexcept { return m_step != 0xff; }
    void m_resetRunning() noexcept { m_step = 0xff; }
};
