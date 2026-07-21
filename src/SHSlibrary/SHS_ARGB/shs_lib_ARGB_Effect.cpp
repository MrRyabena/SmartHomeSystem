#include "shs_lib_ARGB_Effect.h"

#include <FastLED.h>

#include <shs_Process.h>


shs::argb::Effect::Effect(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback, const Effects effect)
    : m_effect(effect), m_leds(leds), m_num_leds(num_leds), m_on_change_callback(on_change_callback)
{}


void shs::argb::Effect::rightShift(CRGB* leds, uint16_t num_leds, uint16_t step)
{
    for (uint16_t i = num_leds; i >= step; --i)
    {
        leds[i] = leds[i - step];
    }
    for (uint16_t i = 0; i < step; ++i)
    {
        leds[i] = CRGB::Black;
    }
}

