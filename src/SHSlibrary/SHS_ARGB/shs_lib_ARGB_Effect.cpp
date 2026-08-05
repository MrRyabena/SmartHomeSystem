#include "shs_lib_ARGB_Effect.h"

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <FastLED.h>
#include <shs_Process.h>


shs::argb::Effect::Effect(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback, const Effects effect)
    : m_effect(effect), m_leds(leds), m_num_leds(num_leds), m_on_change_callback(on_change_callback)
{}


void shs::argb::Effect::rightShift(CRGB* leds, uint16_t num_leds, uint16_t step)
{
    if (leds == nullptr || num_leds == 0 || step == 0)
    {
        return;
    }

    if (step >= num_leds)
    {
        for (uint16_t i = 0; i < num_leds; ++i)
        {
            leds[i] = CRGB::Black;
        }
        return;
    }

    for (uint16_t i = num_leds; i-- > step;)
    {
        leds[i] = leds[i - step];
    }

    for (uint16_t i = 0; i < step; ++i)
    {
        leds[i] = CRGB::Black;
    }
}

void shs::argb::Effect::leftShift(CRGB* leds, uint16_t num_leds, uint16_t step)
{
    if (leds == nullptr || num_leds == 0 || step == 0)
    {
        return;
    }

    if (step >= num_leds)
    {
        for (uint16_t i = 0; i < num_leds; ++i)
        {
            leds[i] = CRGB::Black;
        }
        return;
    }

    for (uint16_t i = 0; i < num_leds - step; ++i)
    {
        leds[i] = leds[i + step];
    }

    for (uint16_t i = num_leds - step; i < num_leds; ++i)
    {
        leds[i] = CRGB::Black;
    }
}

void shs::argb::Effect::centerShift(CRGB* leds, uint16_t num_leds, uint16_t step)
{
    if (leds == nullptr || num_leds == 0 || step == 0)
    {
        return;
    }

    if (step >= (num_leds + 1) / 2)
    {
        for (uint16_t i = 0; i < num_leds; ++i)
        {
            leds[i] = CRGB::Black;
        }
        return;
    }

    const uint16_t center_left = (num_leds - 1) / 2;
    const uint16_t center_right = num_leds / 2;

    for (uint16_t i = 0; i + step <= center_left; ++i)
    {
        leds[i] = leds[i + step];
    }

    for (uint16_t i = num_leds; i-- > center_right + step;)
    {
        leds[i] = leds[i - step];
    }

    for (uint16_t i = center_left - step + 1; i <= center_right + step - 1; ++i)
    {
        leds[i] = CRGB::Black;
    }
}

#endif // SHS_LIB_ARGB_NO_FASTLED
