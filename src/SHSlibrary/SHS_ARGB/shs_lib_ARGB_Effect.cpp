#include "shs_lib_ARGBeffect.h"

#include <FastLED.h>

#include <shs_Process.h>

shs::argb::Effect::Effect(CRGB* const leds, const uint16_t num_leds, std::function<void()> on_change_callback, const Effects effect)
    : m_effect(effect), m_leds(leds), m_num_leds(num_leds), m_on_change_callback(on_change_callback)
{}
