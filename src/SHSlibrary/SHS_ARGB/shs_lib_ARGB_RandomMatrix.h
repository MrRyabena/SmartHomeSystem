#pragma once

#include <FastLed.h>

#include <shs_ProgramTimer.h>
#include <shs_Random.h>

#include "shs_lib_ARGB_Effect.h"


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
    RandomMatrix(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback = nullptr);

    void start() override;
    void tick() override;
    void stop() override;
protected:
    shs::ProgramTimer m_timer;
    shs::Random<uint8_t> m_random_line;
    shs::Random<uint8_t> m_random_color;
    uint8_t m_color;
};
