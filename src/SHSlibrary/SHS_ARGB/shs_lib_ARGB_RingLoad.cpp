// #include "shs_lib_ARGB_RingLoad.h"

// #include <shs_ProgramTime.h>

// #include "shs_lib_ARGB_Effect.h"

// shs::argb::RingLoad::RingLoad(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback = nullptr)
//     : Effect(leds, num_leds, on_change_callback, Effect::Effects::RING_LOAD)
// {}


// void shs::argb::RingLoad::start()
// {

// }

// void shs::argb::RingLoad::tick()
// {
//     // if (!arcDir)
//     // {
//     //     m_start_led += m_leds_in_step;
//     //     m_end_led += arcIncr[counter] + m_leds_in_step;
//     // }
//     // else
//     // {
//     //     m_start_led += arcIncr[counter] + m_leds_in_step;
//     //     m_end_led += m_leds_in_step;
//     // }
//     // if (m_start_led >= NUM_LEDS) m_start_led = (m_start_led - NUM_LEDS);
//     // if (m_end_led >= NUM_LEDS) m_end_led = (m_end_led - NUM_LEDS);

//     // if (++counter >= INCR_AMOUNT)
//     // {
//     //     counter = 0;
//     //     arcDir = !arcDir;
//     //     if (!arcDir)
//     //     {
//     //         colorCounter += 70;
//     //         thisColor = CHSV(colorCounter, 255, 255);
//     //     }
//     // }

//     // if (m_start_led < m_end_led)
//     // {
//     //     fillArc(m_start_led, m_end_led, thisColor, leds);
//     //     fillArc(m_start_led, m_end_led, thisColor, leds2);
//     // }
//     // else
//     // {
//     //     fillArc(m_start_led, NUM_LEDS, thisColor, leds);
//     //     fillArc(m_start_led, NUM_LEDS, thisColor, leds2);
//     //     fillArc(0, m_end_led, thisColor, leds);
//     //     fillArc(0, m_end_led, thisColor, leds2);
//     // }

//     // s = a * t^2 / 2;

//     if (m_rotation_timer.geTimeout() != 0 && m_rotation_timer.check())
//     {
//         m_start_led++;
//         m_end_led++;
//     }

//     auto t = m_getTime();
//     if (t >= m_period)
//     {
//         m_time = shs::ProgramTime::s_milliseconds();
//         t = 0;
//     }

//     // if (t <= m_period / 2)
//     // {
//     //     if (m_end_led >= m_num_leds - m_frame_size) m_end_led = m_num_leds - m_frame_size;
//     //     m_start_led = m_start_led + m_a * t * t / 2;
//     // }
//     // else
//     // {
//     //     m_end_led = m_start_led - m_a * t * t / 2;
//     //     if (m_end_led < 0) m_end_led = 0;
//     // }


//     if (m_start_led >= m_num_leds) m_start_led %= m_num_leds;
//     if (m_end_led >= m_num_leds) m_end_led %= m_num_leds;


//     if (m_start_led < m_end_led)
//     {
//         m_fillRing(m_start_led, m_end_led, m_color);
//     }
//     else
//     {
//         m_fillRing(m_start_led, m_num_leds, m_color);
//         m_fillRing(0, m_end_led, m_color);
//     }
// }


// void shs::argb::RingLoad::stop()
// {

// }

// void shs::argb::RingLoad::m_calculate_a()
// {
//     // S = a * t^2 / 2
//     // a = 2 * S / (T / 2) ^ 2
//     // a = 2 * S / (T^2 * 4)
//     // a = S / (T^2 * 2) 
//     m_a = m_frame_size / (m_period * m_period * 2);
// }

// void shs::argb::RingLoad::m_fillRing(uint16_t start_pos, uint16_t end_pos, CRGB color)
// {
//     for (uint16_t i = start_pos; i < end_pos; i++) m_leds[i] = color;
// }

// shs::t::shs_time_t shs::argb::RingLoad::m_getTime() const
// {
//     return shs::ProgramTime::s_milliseconds() - m_time;
// }
