#pragma once

#include <shs_ProgramTimer.h>
#include <shs_Random.h>

#include "shs_lib_GRGB_Effect.h"

namespace shs
{
    class GRGB_PaletteEffect;
}


class shs::GRGB_PaletteEffect : public shs::GRGB_Effect
{
public:
    GRGB_PaletteEffect(GRGB& grgb, shs::t::shs_time_t period, std::initializer_list<uint32_t> palette)
        : GRGB_Effect(grgb), m_timer(period), m_palette(palette), m_index(0), m_random(0, 0)
    {}

    GRGB_PaletteEffect(GRGB& grgb, shs::t::shs_time_t min_period, shs::t::shs_time_t max_period, std::initializer_list<uint32_t> palette)
        : GRGB_Effect(grgb), m_timer(0), m_palette(palette), m_index(0), m_random(min_period, max_period)
    {
        m_random.autoSeed();
    }

    void setPeriod(const shs::t::shs_time_t period) noexcept { m_timer.setTimeout(period); }
    shs::t::shs_time_t getPeriod() const noexcept { return m_timer.getTimeout(); }

    void setPalette(std::initializer_list<uint32_t> palette) { m_palette = palette; m_index = 0; }
    std::vector<uint32_t> getPalette() const { return m_palette; }

    void start() override { m_timer.reset(); }
    void tick() override
    {
        if (m_timer.check())
        {
            m_grgb.setColor(m_palette[m_index]);
            if (++m_index >= m_palette.size()) m_index = 0;

            if (m_random.getMax() > 0) m_timer.setTimeout(m_random.get());
        }
    }
    void stop() override {}

protected:
    std::vector<uint32_t> m_palette;
    size_t m_index{};
    shs::Random<shs::t::shs_time_t> m_random;
    shs::ProgramTimer m_timer;

};
