#include "shs_lib_ARGB_RandomMatrix.h"

#include <FastLed.h>


shs::argb::RandomMatrix::RandomMatrix(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback,
    shs::t::shs_time_t dt, uint8_t min_color, uint8_t max_color, Direction direction,
    shs::t::shs_float_t min_line_length_ratio, shs::t::shs_float_t max_line_length_ratio)
    : Effect(leds, num_leds, on_change_callback, Effects::NO_EFFECT),
    m_random_line(num_leds* min_line_length_ratio, num_leds* max_line_length_ratio),
    m_random_color(min_color, max_color),
    m_direction(direction),
    m_timer(dt)
{
    m_random_line.autoSeed();
    m_random_color.autoSeed();
    m_color = m_random_color.get();
    m_line = m_random_line.get();
}

void shs::argb::RandomMatrix::start()
{
    // Initialize the random matrix effect
}

void shs::argb::RandomMatrix::tick()
{
    if (m_timer.check())
    {
        if (m_leds == nullptr || m_num_leds == 0)
        {
            return;
        }

        switch (m_direction)
        {
            case Direction::BEGIN:
                rightShift(m_leds, m_num_leds);
                if (m_color != 0)
                {
                    m_leds[0] = CHSV(m_color, 255, 255);
                }
                break;
            case Direction::END:
                leftShift(m_leds, m_num_leds);
                if (m_color != 0)
                {
                    m_leds[m_num_leds - 1] = CHSV(m_color, 255, 255);
                }
                break;
            case Direction::CENTER:
                centerShift(m_leds, m_num_leds);
                if (m_color != 0)
                {
                    const uint16_t center_left = (m_num_leds - 1) / 2;
                    const uint16_t center_right = m_num_leds / 2;

                    m_leds[center_left] = CHSV(m_color, 255, 255);
                    m_leds[center_right] = CHSV(m_color, 255, 255);
                }
                break;
        }

        if (--m_line == 0)
        {
            if (m_color == 0)
            {
                m_color = m_random_color.get();
                m_line = m_random_line.get();
            }
            else
            {
                m_color = 0;
                m_line = m_random_line.get() * 0.4;
            }

            if (m_direction == Direction::CENTER) m_line <<= 2;
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

