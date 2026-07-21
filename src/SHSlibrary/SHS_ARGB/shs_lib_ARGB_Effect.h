#pragma once

#include <stdint.h>
#include <functional>

#include <shs_Process.h>

class CRGB;

namespace shs
{
    namespace argb
    {
        class Effect;
    }
}


class shs::argb::Effect : public shs::Process
{
public:
    enum class Effects : uint16_t { NO_EFFECT, RING_LOAD};

    explicit Effect(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback, Effects effect = Effects::NO_EFFECT);

    Effects getEffect() const { return m_effect; }

    void setCallback(std::function<void()> on_change_callback) { m_on_change_callback = on_change_callback; }

    static void rightShift(CRGB* leds, uint16_t num_leds, uint16_t step = 1);
    static void leftShift(CRGB* leds, uint16_t num_leds, uint16_t step = 1);
    static void centerShift(CRGB* leds, uint16_t num_leds, uint16_t step = 1);


protected:
    std::function<void()> m_on_change_callback;

    CRGB* const m_leds;
    const uint16_t m_num_leds;
    const Effects m_effect;
};
