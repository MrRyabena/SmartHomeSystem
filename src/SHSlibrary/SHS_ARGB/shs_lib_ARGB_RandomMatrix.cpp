#include "shs_lib_ARGB_RandomMatrix.h"

#include <FastLed.h>


shs::argb::RandomMatrix::RandomMatrix(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback)
    : Effect(leds, num_leds, on_change_callback, Effects::NO_EFFECT),
    m_random_line(0, 100), m_random_color(0, 255), m_timer(50)
{
    m_random_line.autoSeed();
    m_random_color.autoSeed();
    m_color = m_random_color.get();
}

void shs::argb::RandomMatrix::start()
{
    // Initialize the random matrix effect
}

void shs::argb::RandomMatrix::tick()
{
    if (m_timer.check())
    {
        auto rand = m_random_line.get();

        rightShift(m_leds, m_num_leds);

        if (rand > 90)
        {
            m_leds[0] = CHSV(m_color, 255, 255);
        }
        else
        {
            m_color = m_random_color.get();
            m_leds[0] = CHSV(0, 255, 0);
        }

        if (m_on_change_callback)
        {
            m_on_change_callback();
        }
    }
}

void shs::argb::RandomMatrix::stop()
{
    // Clean up the random matrix effect
}

