#pragma once


#include <shs_ProgramTimer.h>
#include <shs_types.h>
#include <shs_Process.h>

#include <functional>

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


class shs::lib::Color::RgbEffect : public shs::Process
{
public:

    using callback_t = std::function<void(RGBV8888&)>;

    explicit RgbEffect(const shs::t::shs_time_t dt, const callback_t callback)
        : m_timer(dt), m_callback(callback)
    {}

    virtual ~RgbEffect() = default;


    virtual void setPeriod(const shs::t::shs_time_t period) noexcept = 0;
    virtual shs::t::shs_time_t getPeriod() const noexcept = 0;


protected:
    shs::ProgramTimer m_timer;
    callback_t m_callback;
};
