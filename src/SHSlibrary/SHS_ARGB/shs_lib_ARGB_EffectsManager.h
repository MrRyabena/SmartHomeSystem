#pragma once

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <memory>

#include <stdint.h>

#include <FastLed.h>

#include <shs_Process.h>
#include <shs_types.h>

#include "shs_lib_ARGB_Effect.h"
#include "shs_lib_ARGB_RandomMatrix.h"
#include "shs_lib_ARGB_Fire.h"

namespace shs
{
    namespace argb
    {
        class EffectsManager;
    }
}

class shs::argb::EffectsManager : public shs::Process
{
public:
    EffectsManager(CRGB* leds, uint16_t num_leds);

    void setRandomMatrix(uint8_t min_color = 0, uint8_t max_color = 255,
        RandomMatrix::Direction direction = RandomMatrix::Direction::BEGIN,
        shs::t::shs_time_t dt = 50,
        shs::t::shs_float_t min_line_length_ratio = 0.05,
        shs::t::shs_float_t max_line_length_ratio = 0.5);

    void setFire(uint8_t start_hue = Fire::DEFAULT_HUE_START, uint8_t hue_gap = Fire::DEFAULT_HUE_GAP,
        uint8_t fire_step = Fire::DEFAULT_FIRE_STEP,
        uint8_t min_bright = Fire::DEFAULT_MIN_BRIGHT, uint8_t max_bright = Fire::DEFAULT_MAX_BRIGHT,
        uint8_t min_sat = Fire::DEFAULT_MIN_SAT, uint8_t max_sat = Fire::DEFAULT_MAX_SAT);

    void resetEffects() { m_current_effect = nullptr; }

    void start() override {}
    void tick() override;
    void stop() override {}

protected:
    std::unique_ptr<shs::argb::Effect> m_current_effect;
    CRGB* m_leds;
    uint16_t m_num_leds;
};

#endif // SHS_LIB_ARGB_NO_FASTLED
