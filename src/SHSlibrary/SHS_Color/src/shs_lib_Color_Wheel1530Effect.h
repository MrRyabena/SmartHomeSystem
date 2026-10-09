#pragma once

#include <optional>

#include <shs_types.h>

#include "shs_lib_Color_RgbEffect.h"
#include "shs_lib_Color_Wheel1530.h"

namespace shs::lib::Color
{
    class Wheel1530Effect;
}

class shs::lib::Color::Wheel1530Effect : public shs::lib::Color::RgbEffect
{
public:
    Wheel1530Effect(const shs::t::shs_time_t period, const Wheel1530 start_value = Wheel1530{});

    void setPeriod(shs::t::shs_time_t period) noexcept override;
    shs::t::shs_time_t getPeriod() const noexcept override;

    [[nodiscard]] result_t update() override;

protected:
    Wheel1530 m_value;
};
