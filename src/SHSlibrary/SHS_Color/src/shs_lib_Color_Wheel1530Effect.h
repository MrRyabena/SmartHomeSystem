#pragma once


#include "shs_lib_Color_Effect.h"
#include "shs_lib_Color_Wheel1530.h"
#include <shs_types.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            class Wheel1530Effect;
        }
    }
}

class shs::lib::Color::Wheel1530Effect : public shs::lib::Color::Effect
{
public:
    Wheel1530Effect(const shs::t::shs_time_t period, Effect::callback_t callback, const Wheel1530 start_value = Wheel1530{});

    void setPeriod(shs::t::shs_time_t period) noexcept override;
    shs::t::shs_time_t getPeriod() const noexcept override;

    void start() override {}
    void tick() override;
    void stop() override {}

protected:
    Wheel1530 m_value;
};
