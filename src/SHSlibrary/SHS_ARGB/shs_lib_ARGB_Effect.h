#pragma once

#include <stdint.h>
#include <functional>


class CRGB;

namespace shs
{
    class Process;

    namespace argb
    {
        class ARGBeffect;
    }
}


class shs::argb::ARGBeffect : public shs::Process
{
public:
    enum class Effects : uint16_t { NO_EFFECT, RING_LOAD};

    explicit ARGBeffect(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback, Effects effect = Effects::NO_EFFECT);

    Effects getEffect() const { return m_effect; }

    void setCallback(std::function<void()> on_change_callback) { m_on_change_callback = on_change_callback; }


protected:
    std::function<void()> m_on_change_callback;

    CRGB* const m_leds;
    const uint16_t m_num_leds;
    const Effects m_effect;
};
