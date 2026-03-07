#pragma once

#include <shs_lib_GRGB_Effect.h>
#include <shs_ProgramTimer.h>

namespace shs
{
    class GRGB_Breathing;
}


class shs::GRGB_Breathing : public shs::GRGB_Effect
{
public:
    GRGB_Breathing(GRGB& grgb, shs::t::shs_time_t dt, int16_t increment = 1,
        uint16_t start_brightness = 0, uint8_t min_brightness = 0, uint8_t max_brightness = 0xff)
        : GRGB_Effect(grgb), m_timer(dt),
        m_min_brightness(min_brightness), m_max_brightness(max_brightness), m_brightness(start_brightness),
        m_increment(increment)
    {}

    void start() override { m_timer.reset(); }
    void tick() override
    {
        if (m_timer.check())
        {
            m_grgb.setBrightness(m_brightness);


            m_brightness += m_increment;
            if (m_brightness >= m_max_brightness)
            {
                m_brightness = m_max_brightness;
                m_increment = std::abs(m_increment) * (-1);
            }
            else if (m_brightness <= m_min_brightness)
            {
                m_brightness = m_min_brightness;
                m_increment = std::abs(m_increment);
            }
        }
    }
    void stop() override {}

protected:
    shs::ProgramTimer m_timer;

    uint8_t m_min_brightness;
    uint8_t m_max_brightness;

    int16_t m_brightness;
    int16_t m_increment;
};
