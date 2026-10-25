#pragma once

#include <shs_settings_private.h>

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <stdint.h>

#include <FastLED.h>

#include <shs_ProgramTimer.h>
#include <shs_types.h>

#include "shs_lib_ARGB_Effect.h"

namespace shs::argb
{
    class Fire;
}


class shs::argb::Fire : public shs::argb::Effect
{
public:
    static constexpr uint8_t DEFAULT_HUE_START = 0;
    static constexpr uint8_t DEFAULT_HUE_GAP = 21;
    static constexpr uint8_t DEFAULT_FIRE_STEP = 15;
    static constexpr uint8_t DEFAULT_MIN_BRIGHT = 70;
    static constexpr uint8_t DEFAULT_MAX_BRIGHT = 255;
    static constexpr uint8_t DEFAULT_MIN_SAT = 245;
    static constexpr uint8_t DEFAULT_MAX_SAT = 255;
    static constexpr auto DEFAULT_PERIOD = 20;

    Fire(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback = nullptr,
        uint8_t start_hue = DEFAULT_HUE_START, uint8_t hue_gap = DEFAULT_HUE_GAP, uint8_t fire_step = DEFAULT_FIRE_STEP,
        uint8_t min_bright = DEFAULT_MIN_BRIGHT, uint8_t max_bright = DEFAULT_MAX_BRIGHT,
        uint8_t min_sat = DEFAULT_MIN_SAT, uint8_t max_sat = DEFAULT_MAX_SAT);

    void start() override { m_timer.reset(); }
    void tick() override;
    void stop() override {}

    CHSV getFireColor(const uint16_t val);

    void setPeriod(const shs::t::shs_time_t period) noexcept { m_timer.setTimeout(period); m_timer.reset(); }
    [[nodiscard]] shs::t::shs_time_t getPeriod() const noexcept { return m_timer.getTimeout(); }

    void setStartHue(uint8_t start_hue) noexcept { m_start_hue = start_hue; }
    [[nodiscard]] uint8_t getStartHue() const noexcept { return m_start_hue; }
    void setHueGap(uint8_t hue_gap) noexcept { m_hue_gap = hue_gap; }
    [[nodiscard]] uint8_t getHueGap() const noexcept { return m_hue_gap; }
    void setMinBrightness(uint8_t min_brightness) noexcept { m_min_brightness = min_brightness; }
    [[nodiscard]] uint8_t getMinBrightness() const noexcept { return m_min_brightness; }
    void setMaxBrightness(uint8_t max_brightness) noexcept { m_max_brightness = max_brightness; }
    [[nodiscard]] uint8_t getMaxBrightness() const noexcept { return m_max_brightness; }
    void setMinSaturation(uint8_t min_saturation) noexcept { m_min_saturation = min_saturation; }
    [[nodiscard]] uint8_t getMinSaturation() const noexcept { return m_min_saturation; }
    void setMaxSaturation(uint8_t max_saturation) noexcept { m_max_saturation = max_saturation; }
    [[nodiscard]] uint8_t getMaxSaturation() const noexcept { return m_max_saturation; }

protected:
    shs::ProgramTimer m_timer;
    int m_counter{};

    uint8_t m_start_hue;
    uint8_t m_hue_gap;
    uint8_t m_fire_step;
    uint8_t m_min_brightness;
    uint8_t m_max_brightness;
    uint8_t m_min_saturation;
    uint8_t m_max_saturation;
};

#endif  // #ifndef SHS_LIB_ARGB_NO_FASTLED
