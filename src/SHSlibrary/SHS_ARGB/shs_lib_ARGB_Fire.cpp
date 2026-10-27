#include "shs_lib_ARGB_Fire.h"

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <shs_algorithm.h>

#include "shs_lib_ARGB_Effects.h"

shs::argb::Fire::Fire(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback, uint8_t start_hue, uint8_t hue_gap, uint8_t fire_step, uint8_t min_bright, uint8_t max_bright, uint8_t min_sat, uint8_t max_sat)
    : Effect(leds, num_leds, on_change_callback, Effects::FIRE_LINE_PERLIN), m_timer(DEFAULT_PERIOD),
    m_start_hue(start_hue), m_hue_gap(hue_gap), m_fire_step(fire_step),
    m_min_brightness(min_bright), m_max_brightness(max_bright),
    m_min_saturation(min_sat), m_max_saturation(max_sat)
{}

void shs::argb::Fire::tick()
{
    if (m_timer.check())
    {
        uint16_t this_pos{}, last_pos{};
        for (auto i = 0u; i < m_num_leds; i++)
        {
            m_leds[i] = getFireColor((inoise8(i * m_fire_step, m_counter)));
        }
        m_counter += 20;

        if (m_on_change_callback) m_on_change_callback();
    }
}

CHSV shs::argb::Fire::getFireColor(const uint16_t val)
{
    // the bigger val, the stronger the color shift, the lower the saturation and the higher the brightness
    return CHSV(
        m_start_hue + shs::map(static_cast<int>(val), 0, 255, 0, m_hue_gap),                              // H
        shs::clamp(shs::map(static_cast<int>(val), 0, 255, m_max_saturation, m_min_saturation), 0, 255),  // S
        shs::clamp(shs::map(static_cast<int>(val), 0, 255, m_min_brightness, m_max_brightness), 0, 255)   // V
    );
}

#endif  // #ifndef SHS_LIB_ARGB_NO_FASTLED
