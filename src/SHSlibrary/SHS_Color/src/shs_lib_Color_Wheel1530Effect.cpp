#include "shs_lib_Color_Wheel1530Effect.h"

#include "shs_lib_Color_cast.h"

#include <utility>

shs::lib::Color::Wheel1530Effect::Wheel1530Effect(const shs::t::shs_time_t period, const Wheel1530 start_value)
    : shs::lib::Color::RgbEffect(period / 1530), m_value(start_value)
{}

void shs::lib::Color::Wheel1530Effect::setPeriod(shs::t::shs_time_t period) noexcept
{
    m_timer.setTimeout(period / 1530);
}

shs::t::shs_time_t shs::lib::Color::Wheel1530Effect::getPeriod() const noexcept
{
    return m_timer.getTimeout() * 1530;
}

shs::lib::Color::Wheel1530Effect::result_t shs::lib::Color::Wheel1530Effect::update()
{
    if (m_timer.check())
    {
        ++m_value;

        using namespace shs::lib::Color;
        return result_t{ std::make_optional(color_cast<RGB888>(m_value)), std::nullopt };
    }
    return result_t{ std::nullopt, std::nullopt };
}


