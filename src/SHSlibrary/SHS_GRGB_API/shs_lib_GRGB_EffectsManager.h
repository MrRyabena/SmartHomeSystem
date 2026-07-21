#pragma once

#include <memory>

#include "shs_lib_GRGB_Effect.h"
#include "shs_lib_GRGB_Breathing.h"
#include "shs_lib_GRGB_ColorWheel.h"
#include "shs_lib_GRGB_RandomColorEffect.h" 

namespace shs
{
    class GRGB_EffectsManager;
}


class shs::GRGB_EffectsManager : public shs::GRGB_Effect
{
public:
    GRGB_EffectsManager(GRGB& grgb) : GRGB_Effect(grgb) {}

    void setColorWheel(shs::t::shs_time_t dt, int16_t shift = 1) { m_e_color_wheel = std::make_unique<shs::ColorWheel>(m_grgb, dt, shift); }
    void setBreathing(shs::t::shs_time_t dt, int16_t increment = 1,
        uint16_t start_brightness = 0, uint8_t min_brightness = 0, uint8_t max_brightness = 0xff)
    {
        m_e_breathing = std::make_unique<shs::GRGB_Breathing>(m_grgb, dt, increment, start_brightness, min_brightness, max_brightness);
    }
    void setRandomColorEffect(shs::t::shs_time_t min_period, shs::t::shs_time_t max_period, uint32_t min_color = 0, uint32_t max_color = 1529)
    {
        m_e_random_color = std::make_unique<shs::GRGB_RandomColorEffect>(m_grgb, min_period, max_period, min_color, max_color);
    }

    void resetColorWheel() { m_e_color_wheel = nullptr; }
    void resetBreathing() { m_e_breathing = nullptr; }
    void resetRandomColorEffect() { m_e_random_color = nullptr; }

    void start()
    {
        if (m_e_color_wheel) m_e_color_wheel->start();
        if (m_e_breathing) m_e_breathing->start();
        if (m_e_random_color) m_e_random_color->start();
    }

    void tick()
    {
        if (m_e_color_wheel) m_e_color_wheel->tick();
        if (m_e_breathing) m_e_breathing->tick();
        if (m_e_random_color) m_e_random_color->tick();
    }

    void stop()
    {
        if (m_e_color_wheel) m_e_color_wheel->stop();
        if (m_e_breathing) m_e_breathing->stop();
        if (m_e_random_color) m_e_random_color->stop();
    }

protected:
    std::unique_ptr<shs::ColorWheel> m_e_color_wheel;
    std::unique_ptr<shs::GRGB_Breathing> m_e_breathing;
    std::unique_ptr<shs::GRGB_RandomColorEffect> m_e_random_color;
};
