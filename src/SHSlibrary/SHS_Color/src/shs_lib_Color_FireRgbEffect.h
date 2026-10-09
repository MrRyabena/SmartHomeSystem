#pragma once

#include <shs_ProgramTimer.h>
#include <shs_Random.h>
#include <shs_types.h>

#include "shs_lib_Color_RgbEffect.h"

namespace shs::lib::Color
{
    class FireRgbEffect;
}


class shs::lib::Color::FireRgbEffect : public RgbEffect
{
public:
    static constexpr shs::t::shs_float_t DEFAULT_SMOOTH_K = 0.15f;
    static constexpr uint8_t DEFAULT_START_HUE = 0;
    static constexpr uint8_t DEFAULT_HUE_GAP = 10;
    static constexpr uint8_t DEFAULT_MIN_BRIGHTNESS = 100;
    static constexpr uint8_t DEFAULT_MAX_BRIGHTNESS = 255;
    static constexpr uint8_t DEFAULT_MIN_SATURATION = 255;
    static constexpr uint8_t DEFAULT_MAX_SATURATION = 255;

    /**
     * @brief Constructs a FireRgbEffect with the specified parameters.
     * @param m_start_hue The starting hue for the fire effect (0-255), (0 red, 80 green, 140 blue, 190 pink).
     * @param m_hue_gap The gap in hue for the fire effect (the higher the value, the further the color shift).
     * @param m_smooth_k The smoothing factor for the fire effect (0.0-1.0).
     * @param m_duration The duration of the fire effect in milliseconds.
     * @param m_min_brightness The minimum brightness for the fire effect (0-255).
     * @param m_max_brightness The maximum brightness for the fire effect (0-255).
     * @param m_min_saturation The minimum saturation for the fire effect (0-255).
     * @param m_max_saturation The maximum saturation for the fire effect (0-255).
     */
    explicit FireRgbEffect(uint8_t start_hue = DEFAULT_START_HUE, uint8_t hue_gap = DEFAULT_HUE_GAP,
        shs::t::shs_float_t smooth_k = DEFAULT_SMOOTH_K, shs::t::shs_time_t duration = DEFAULT_DURATION,
        uint8_t min_brightness = DEFAULT_MIN_BRIGHTNESS, uint8_t max_brightness = DEFAULT_MAX_BRIGHTNESS,
        uint8_t min_saturation = DEFAULT_MIN_SATURATION, uint8_t max_saturation = DEFAULT_MAX_SATURATION);

    [[nodiscard]] result_t update() override;

    void setPeriod(const shs::t::shs_time_t period) noexcept override;
    [[nodiscard]] shs::t::shs_time_t getPeriod() const noexcept override;

    void setStartHue(uint8_t start_hue) noexcept { m_start_hue = start_hue; }
    [[nodiscard]] uint8_t getStartHue() const noexcept { return m_start_hue; }
    void setHueGap(uint8_t hue_gap) noexcept { m_hue_gap = hue_gap; }
    [[nodiscard]] uint8_t getHueGap() const noexcept { return m_hue_gap; }
    void setSmoothK(shs::t::shs_float_t smooth_k) noexcept { m_smooth_k = std::clamp(smooth_k, 0.0f, 1.0f); }
    [[nodiscard]] shs::t::shs_float_t getSmoothK() const noexcept { return m_smooth_k; }
    void setMinBrightness(uint8_t min_brightness) noexcept { m_min_brightness = min_brightness; }
    [[nodiscard]] uint8_t getMinBrightness() const noexcept { return m_min_brightness; }
    void setMaxBrightness(uint8_t max_brightness) noexcept { m_max_brightness = max_brightness; }
    [[nodiscard]] uint8_t getMaxBrightness() const noexcept { return m_max_brightness; }
    void setMinSaturation(uint8_t min_saturation) noexcept { m_min_saturation = min_saturation; }
    [[nodiscard]] uint8_t getMinSaturation() const noexcept { return m_min_saturation; }
    void setMaxSaturation(uint8_t max_saturation) noexcept { m_max_saturation = max_saturation; }
    [[nodiscard]] uint8_t getMaxSaturation() const noexcept { return m_max_saturation; }

protected:
    shs::Random<uint8_t> m_random;

    shs::t::shs_float_t m_smooth_k;
    shs::t::shs_float_t m_fire_value;

    uint8_t m_fire_rnd;
    uint8_t m_timeout_counter;
    uint8_t m_start_hue;
    uint8_t m_hue_gap;
    uint8_t m_min_brightness;
    uint8_t m_max_brightness;
    uint8_t m_min_saturation;
    uint8_t m_max_saturation;


    template<typename T>
    constexpr T map(T x, T in_min, T in_max, T out_min, T out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

};
