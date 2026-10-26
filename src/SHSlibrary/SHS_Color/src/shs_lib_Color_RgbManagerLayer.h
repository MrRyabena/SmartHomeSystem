#pragma once

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "shs_lib_Color_RgbManagerLayerInterface.h"
#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_RgbController.h"
#include "shs_lib_Color_RgbEffect.h"
#include "shs_lib_Color_BrightSmoothFilter.h"
#include "shs_lib_Color_FadeRgbFilter.h"
#include "shs_lib_Color_RgbvFilter.h"


namespace shs::lib::Color
{
    class RgbManagerLayer;
}


class shs::lib::Color::RgbManagerLayer : public RgbManagerLayerInterface
{
public:
    using effect_id_t = uint16_t;

    RgbManagerLayer(RGBV8888 base_color = RGBV8888(0, 0, 0, 255), std::vector<std::unique_ptr<RgbEffect>> effects = {});
    RgbManagerLayer(BrightSmoothFilter bright_filter, FadeRgbFilter fade_filter, RGBV8888 base_color, std::vector<std::unique_ptr<RgbEffect>> effects = {});

    /**
     * @brief Apply the the layer filters and effects.
     * @param color The base color to modify with the layer filters and effects.
     * @return true if the color was changed, false otherwise.
     * @note This method should be frequently called in loop.
     */
    [[nodiscard]] bool apply(RGBV8888& color) override;

    void setup() override {}

    void setColor(const RGB888 color) override;
    RGB888 getColor() const override { return m_color.getRgb(); }

    void setBrightness(const uint8_t brightness) override;
    uint8_t getBrightness() const override { return m_color.value; }

    void setValue(const RGBV8888 color) override { m_color = color; }
    RGBV8888 getValue() const override { return m_color; }

    [[nodiscard]] effect_id_t pushEffect(std::unique_ptr<RgbEffect> effect) { m_effects.push_back(std::move(effect)); return m_effects.size() - 1; }
    effect_id_t popEffect() { if (!m_effects.empty()) m_effects.pop_back();  return m_effects.size(); }
    void removeEffect(const effect_id_t id) { if (id < m_effects.size()) m_effects.erase(m_effects.begin() + id); }
    void clearEffects() { m_effects.clear(); }

    void enableBrightSmooth() override { m_brightness_filter.enable(); }
    void disableBrightSmooth() override { m_brightness_filter.disable(); }
    void setBrightSmoothStepTimeout(const shs::t::shs_time_t step_timeout) override { m_brightness_filter.setStepTimeout(step_timeout); }
    void setBrightSmoothStep(const uint8_t step) override { m_brightness_filter.setStep(step); }
    [[nodiscard]] shs::t::shs_time_t getBrightSmoothStepTimeout() const override { return m_brightness_filter.getStepTimeout(); }
    [[nodiscard]] uint8_t getBrightSmoothStep() const override { return m_brightness_filter.getStep(); }

    void enableFade() override { m_fade_filter.enable(); }
    void disableFade() override { m_fade_filter.disable(); }
    void setFadePeriod(const shs::t::shs_time_t period) override { m_fade_filter.setPeriod(period); }
    [[nodiscard]] shs::t::shs_time_t getFadePeriod() const override { return m_fade_filter.getPeriod(); }

protected:
    std::vector<std::unique_ptr<RgbEffect>> m_effects;
    RGBV8888 m_color;
    FadeRgbFilter m_fade_filter;
    BrightSmoothFilter m_brightness_filter;
    bool m_active;
};
