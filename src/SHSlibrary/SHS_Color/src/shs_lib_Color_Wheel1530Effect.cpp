#include "shs_lib_Color_Wheel1530Effect.h"

#include "shs_lib_Color_cast.h"

shs::lib::Color::Wheel1530Effect::Wheel1530Effect(const shs::t::shs_time_t period, Effect::callback_t callback, const Wheel1530 start_value)
    : shs::lib::Color::Effect(period / 1530, callback), m_value(start_value)
{}

void shs::lib::Color::Wheel1530Effect::setPeriod(shs::t::shs_time_t period) noexcept
{
    m_timer.setTimeout(period / 1530);
}

shs::t::shs_time_t shs::lib::Color::Wheel1530Effect::getPeriod() const noexcept
{
    return m_timer.getTimeout() * 1530;
}

void shs::lib::Color::Wheel1530Effect::tick()
{
    if (m_timer.check())
    {
        ++m_value;
        
        using namespace shs::lib::Color;
        if (m_callback) m_callback(color_cast<RGBV8888>(m_value));
    }
}


