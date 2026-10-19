#pragma once

#include <memory>

#include "shs_lib_Color_RgbvFilter.h"
#include "shs_lib_Color_RgbController.h"
#include "shs_lib_Color_RgbEffect.h"
#include "shs_lib_Color_RGBV8888.h"

namespace shs::lib::Color
{
    class RgbManagerLayerInterface;
}

class shs::lib::Color::RgbManagerLayerInterface : public shs::lib::Color::RgbController, public RgbvFilter
{
public:
    using effect_id_t = uint16_t;

    virtual ~RgbManagerLayerInterface() = default;

    virtual effect_id_t pushEffect(std::unique_ptr<RgbEffect> effect) = 0;
    virtual effect_id_t popEffect() = 0;
    virtual void removeEffect(const effect_id_t id) = 0;
    virtual void clearEffects() = 0;

    virtual void enableBrightSmooth() = 0;
    virtual void disableBrightSmooth() = 0;
    virtual void setBrightSmoothStepTimeout(const shs::t::shs_time_t step_timeout) = 0;
    virtual void setBrightSmoothStep(const uint8_t step) = 0;
    virtual shs::t::shs_time_t getBrightSmoothStepTimeout() const = 0;
    virtual uint8_t getBrightSmoothStep() const = 0;

    virtual void enableFade() = 0;
    virtual void disableFade() = 0;
    virtual void setFadePeriod(const shs::t::shs_time_t period) = 0;
    virtual shs::t::shs_time_t getFadePeriod() const = 0;

};
