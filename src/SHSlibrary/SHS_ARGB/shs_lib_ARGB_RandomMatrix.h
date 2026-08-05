#pragma once

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <FastLed.h>

#include <shs_ProgramTimer.h>
#include <shs_Random.h>
#include <shs_types.h>

#include "shs_lib_ARGB_Effect.h"
#include "shs_lib_ARGB_RandomMatrix_Direction.h"

namespace shs
{
    namespace argb
    {
        class RandomMatrix;
    }
}


class shs::argb::RandomMatrix : public shs::argb::Effect
{
public:
    using Direction = shs::argb::RandomMatrix_Direction;

    RandomMatrix(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback = nullptr,
        shs::t::shs_time_t dt = 50, uint8_t min_color = 0, uint8_t max_color = 255,
        Direction direction = Direction::BEGIN,
        shs::t::shs_float_t min_line_length_ratio = 0.05,
        shs::t::shs_float_t max_line_length_ratio = 0.5);

    void start() override;
    void tick() override;
    void stop() override;
protected:
    shs::ProgramTimer m_timer;
    shs::Random<uint8_t> m_random_line;
    shs::Random<uint8_t> m_random_color;
    uint8_t m_line;
    uint8_t m_color;
    Direction m_direction;
};

#endif // SHS_LIB_ARGB_NO_FASTLED
