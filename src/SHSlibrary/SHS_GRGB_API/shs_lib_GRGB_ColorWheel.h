#pragma once

#include "shs_lib_GRGB_Effect.h"

#include <shs_ProgramTimer.h>
#include <shs_types.h>

namespace shs
{
    class ColorWheel;
}

class shs::ColorWheel : public shs::GRGB_Effect
{
public:
    ColorWheel(GRGB& grgb, shs::t::shs_timer_t dt, int16_t shift = 1) : GRGB_Effect(grgb), m_timer(dt), m_shift(shift) {}
    ColorWheel(GRGB& grgb, shs::t::shs_timer_t period, int16_t shift = 1) : GRGB_Effect(grgb), m_timer(period / M_HIGH_COLOR_BOUND), m_shift(shift) {}

    void setDt(const shs::t::shs_timer_t dt) { m_timer.setTimeout(dt); }
    shs::t::shs_timer_t getDt() const { return m_timer.getTimeout(); }

    void setPeriod(const shs::t::shs_timer_t period) { m_timer.setTimeout(period / M_HIGH_COLOR_BOUND); }
    shs::t::shs_timer_t getPeriod() const { return m_timer.getTimerout() * M_HIGH_COLOR_BOUND; }

    void start() override { m_timer.reset(); }
    void tick() override
    {
        if (m_timer.check()) m_grgb.setWheel(m_color);

        m_color += shift;
        if (m_color >= M_HIGH_COLOR_BOUND) m_color %= M_HIGH_COLOR_BOUND;
    }

    void stop() override {}

protected:
    shs::ProgramTimer m_timer;
    uint16_t m_color{};
    int16_t m_shift;

    static constexpr auto M_HIGH_COLOR_BOUND = 1531;  // m_color must be <= M_HIGH_COLOR_BOUND

};
