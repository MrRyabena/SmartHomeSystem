#pragma once

#include "shs_lib_Color_RgbManagerLayerInterface.h"
#include "shs_lib_Color_RgbManagerLayerApiCommands.h"
#include "shs_lib_Color_RgbManagerVirtual.h"

namespace shs::lib::Color
{
    class RgbManagerApiLayerWrapper;
}


class shs::lib::Color::RgbManagerApiLayerWrapper : public RgbManagerLayerInterface
{
public:
    using layer_id_t = RgbManagerVirtual::layer_id_t;

    RgbManagerApiLayerWrapper(RgbManagerVirtual& parent, const layer_id_t layer_id);

    effect_id_t pushEffect(std::unique_ptr<RgbEffect> effect) override;
    effect_id_t popEffect() override;
    void removeEffect(const effect_id_t id) override;
    void clearEffects() override { m_parent.manageLayer(RgbManagerLayerApiCommands::CLEAR_EFFECTS, m_layer_id); }

    void enableBrightSmooth() override { m_parent.manageLayer(RgbManagerLayerApiCommands::ENABLE_BRIGHT_SMOOTH, m_layer_id); }
    void disableBrightSmooth() override { m_parent.manageLayer(RgbManagerLayerApiCommands::DISABLE_BRIGHT_SMOOTH, m_layer_id); }
    void setBrightSmoothStepTimeout(const shs::t::shs_time_t timeout) override;
    void setBrightSmoothStep(const uint8_t step) override;

    void enableFade() override { m_parent.manageLayer(RgbManagerLayerApiCommands::ENABLE_FADE, m_layer_id); }
    void disableFade() override { m_parent.manageLayer(RgbManagerLayerApiCommands::DISABLE_FADE, m_layer_id); }
    void setFadePeriod(const shs::t::shs_time_t period) override;

    shs::t::shs_time_t getBrightSmoothStepTimeout() const override { return 0; }    // TODO: temporary not implemented
    uint8_t getBrightSmoothStep() const override { return 0; }                      // TODO
    shs::t::shs_time_t getFadePeriod() const override { return 0; }                 // TODO

    bool apply(RGBV8888& color) override { return false; }

    void setup() override {}
    void setColor(const RGB888 color) override {}
    RGB888 getColor() const override { return RGB888(); }                           // TODO
    void setBrightness(const uint8_t brightness) override {}
    uint8_t getBrightness() const override { return 0; }                            // TODO

protected:
    RgbManagerVirtual& m_parent;
    layer_id_t m_layer_id;
};

