#pragma once

#include <optional>

#include <shs_ProgramTimer.h>
#include <shs_types.h>
#include <shs_Process.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct RGBV8888;
            class RgbEffect;
        }
    }
}


class shs::lib::Color::RgbEffect
{
public:
    explicit RgbEffect(const shs::t::shs_time_t dt)
        : m_timer(dt)
    {}

    virtual ~RgbEffect() = default;

    [[nodiscard]] virtual std::optional<RGBV8888> getColor() = 0;

    virtual void setPeriod(const shs::t::shs_time_t period) noexcept = 0;
    virtual shs::t::shs_time_t getPeriod() const noexcept = 0;

protected:
    shs::ProgramTimer m_timer;
};
