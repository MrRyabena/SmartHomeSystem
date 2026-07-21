#include "shs_lib_ARGB_EffectsManager.h"

#include <FastLed.h>

#include "shs_lib_ARGB_RandomMatrix.h"

shs::argb::EffectsManager::EffectsManager(CRGB* leds, uint16_t num_leds)
    : m_leds(leds), m_num_leds(num_leds)
{}

void shs::argb::EffectsManager::setRandomMatrix(uint8_t min_color, uint8_t max_color, shs::t::shs_time_t dt, shs::t::shs_float_t min_line_length_ratio, shs::t::shs_float_t max_line_length_ratio)
{
    m_current_effect = std::make_unique<shs::argb::RandomMatrix>(m_leds, m_num_leds,
        []() { FastLED.show(); },
        dt, min_color, max_color, min_line_length_ratio, max_line_length_ratio);
}

void shs::argb::EffectsManager::tick()
{
    if (m_current_effect)
    {
        m_current_effect->tick();
    }
}
