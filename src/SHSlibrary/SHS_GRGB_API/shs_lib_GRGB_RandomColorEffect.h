#pragma once

#include <shs_ProgramTimer.h>
#include <shs_Random.h>

#include "shs_lib_GRGB_Effect.h"

namespace shs
{
    class GRGB_RandomColorEffect;
}

class shs::GRGB_RandomColorEffect : public shs::GRGB_Effect
{
public:

    GRGB_RandomColorEffect(GRGB& grgb, const t::shs_time_t min_period, const t::shs_time_t max_period, const uint32_t min_color = 0, const uint32_t max_color = 1529)
        : GRGB_Effect(grgb), m_timer(0), m_random_time(min_period, max_period), m_random_color(min_color, max_color)
    {
        m_random_time.autoSeed();
        m_random_color.autoSeed();
    }

    void setPeriod(shs::t::shs_time_t min_period, shs::t::shs_time_t max_period) noexcept
    {
        m_random_time.setRange(min_period, max_period);
    }

    void setColorRange(uint32_t min_color, uint32_t max_color) noexcept
    {
        m_random_color.setRange(min_color, max_color);
    }

    void start() override { m_timer.reset(); }
    void tick() override
    {
        if (m_timer.check())
        {
            m_grgb.setWheel(m_random_color.get());
            m_timer.setTimeout(m_random_time.get());
        }
    }
    void stop() override {}

protected:
    shs::Random<shs::t::shs_time_t> m_random_time;
    shs::Random<uint32_t> m_random_color;
    shs::ProgramTimer m_timer;

};
