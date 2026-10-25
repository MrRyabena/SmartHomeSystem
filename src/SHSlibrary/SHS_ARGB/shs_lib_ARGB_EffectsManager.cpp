#include "shs_lib_ARGB_EffectsManager.h"

#ifndef SHS_LIB_ARGB_NO_FASTLED
#include <FastLed.h>


shs::argb::EffectsManager::EffectsManager(CRGB* leds, uint16_t num_leds)
    : m_leds(leds), m_num_leds(num_leds)
{}

void shs::argb::EffectsManager::setRandomMatrix(uint8_t min_color, uint8_t max_color, RandomMatrix::Direction direction, shs::t::shs_time_t dt, shs::t::shs_float_t min_line_length_ratio, shs::t::shs_float_t max_line_length_ratio)
{
    m_current_effect = std::make_unique<shs::argb::RandomMatrix>(m_leds, m_num_leds,
        []() { FastLED.show(); },
        dt, min_color, max_color, direction, min_line_length_ratio, max_line_length_ratio);
}

void shs::argb::EffectsManager::setFire(uint8_t start_hue,
    uint8_t hue_gap, uint8_t fire_step,
    uint8_t min_bright, uint8_t max_bright,
    uint8_t min_sat, uint8_t max_sat)
{
    m_current_effect = std::make_unique<shs::argb::Fire>(m_leds, m_num_leds,
        []() { FastLED.show(); },
        start_hue, hue_gap, fire_step, min_bright, max_bright, min_sat, max_sat);
}

void shs::argb::EffectsManager::tick()
{
    if (m_current_effect)
    {
        m_current_effect->tick();
    }
}

#endif  // #ifndef SHS_LIB_ARGB_NO_FASTLED
