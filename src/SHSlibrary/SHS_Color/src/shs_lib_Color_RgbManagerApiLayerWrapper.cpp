#include "shs_lib_Color_RgbManagerApiLayerWrapper.h"

#include <shs_types.h>

#include "shs_lib_Color_Wheel1530Effect.h"
#include "shs_lib_Color_FireRgbEffect.h"



shs::lib::Color::RgbManagerApiLayerWrapper::RgbManagerApiLayerWrapper(RgbManagerVirtual& parent, const layer_id_t layer_id)
    : m_parent(parent), m_layer_id(layer_id)
{}

shs::lib::Color::RgbManagerApiLayerWrapper::effect_id_t shs::lib::Color::RgbManagerApiLayerWrapper::pushEffect(std::unique_ptr<RgbEffect> effect)
{
    shs::ByteCollector<> bc(32);

    bc.push_back(RgbManagerLayerApiCommands::PUSH_EFFECT, 1);
    bc.push_back(effect->getType(), 1);
    switch (effect->getType())
    {
        case RgbEffectType::WHEEL1530:
            {
                auto wheel_effect = static_cast<Wheel1530Effect*>(effect.get());
                if (wheel_effect)
                {
                    bc.push_back(wheel_effect->getPeriod());
                    bc.push_back(0, 1);
                }
            }
            break;
        case RgbEffectType::FIRE:
            {
                auto fire_effect = static_cast<FireRgbEffect*>(effect.get());
                if (fire_effect)
                {
                    bc.push_back(fire_effect->getStartHue(), 1);
                    bc.push_back(fire_effect->getHueGap(), 1);
                    bc.push_back(static_cast<shs::t::shs_fixed_t>(fire_effect->getSmoothK()));
                    bc.push_back(fire_effect->getPeriod());
                    bc.push_back(fire_effect->getMinBrightness(), 1);
                    bc.push_back(fire_effect->getMaxBrightness(), 1);
                    bc.push_back(fire_effect->getMinSaturation(), 1);
                    bc.push_back(fire_effect->getMaxSaturation(), 1);
                }
            }
            break;
        default: doutln("Unknown effect type"); break;
    }

    m_parent.manageLayer(std::move(bc), m_layer_id);

    return effect_id_t();
}

shs::lib::Color::RgbManagerApiLayerWrapper::effect_id_t shs::lib::Color::RgbManagerApiLayerWrapper::popEffect()
{
    m_parent.manageLayer(RgbManagerLayerApiCommands::POP_EFFECT, m_layer_id);
    return effect_id_t();
}

void shs::lib::Color::RgbManagerApiLayerWrapper::removeEffect(const effect_id_t id)
{
    shs::ByteCollector<> bc(1 + sizeof(id));
    bc.push_back(RgbManagerLayerApiCommands::REMOVE_EFFECT, 1);
    bc.push_back(id);

    m_parent.manageLayer(std::move(bc), m_layer_id);
}

void shs::lib::Color::RgbManagerApiLayerWrapper::setBrightSmoothStepTimeout(const shs::t::shs_time_t timeout)
{
    shs::ByteCollector<> bc(1 + sizeof(timeout));
    bc.push_back(RgbManagerLayerApiCommands::SET_BRIGHT_SMOOTH_STEP_TIMEOUT, 1);
    bc.push_back(timeout);

    m_parent.manageLayer(std::move(bc), m_layer_id);
}

void shs::lib::Color::RgbManagerApiLayerWrapper::setBrightSmoothStep(const uint8_t step)
{
    shs::ByteCollector<> bc(2);
    bc.push_back(RgbManagerLayerApiCommands::SET_BRIGHT_SMOOTH_STEP, 1);
    bc.push_back(step, 1);

    m_parent.manageLayer(std::move(bc), m_layer_id);
}

void shs::lib::Color::RgbManagerApiLayerWrapper::setFadePeriod(const shs::t::shs_time_t period)
{
    shs::ByteCollector<> bc(1 + sizeof(period));
    bc.push_back(RgbManagerLayerApiCommands::SET_FADE_PERIOD, 1);
    bc.push_back(period);

    m_parent.manageLayer(std::move(bc), m_layer_id);
}
