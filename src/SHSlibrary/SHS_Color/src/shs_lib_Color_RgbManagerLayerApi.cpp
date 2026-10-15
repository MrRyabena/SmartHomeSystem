#include "shs_lib_Color_RgbManagerLayerApi.h"

#include <shs_utils.h>

#include <shs_lib_APIids.h>

#include "shs_lib_Color_RgbEffectType.h"
#include "shs_lib_Color_Wheel1530Effect.h"
#include "shs_lib_Color_Wheel1530.h"
#include "shs_lib_Color_FireRgbEffect.h"

shs::lib::Color::RgbManagerLayerApi::RgbManagerLayerApi(std::shared_ptr<RgbManagerLayer> layer, shs::t::shs_ID_t id)
    : shs::API(id.setComponentID(shs::etoi(shs::lib::APIids::COLOR_RGB_MANAGER_LAYER_API))), m_layer(layer)
{}

shs::DTPpacket shs::lib::Color::RgbManagerLayerApi::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    const auto id = handle(it, m_layer);

    if (id)
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (static_cast<Commands>(it.read()))
        {
            case Commands::PUSH_EFFECT: return m_createAnswerId(Commands::PUSHED_EFFECT_ID, *id, it); break;
            case Commands::POP_EFFECT:  return m_createAnswerId(Commands::POPPED_EFFECT_ID, *id, it); break;
            default: break;
        }
    }

    return shs::DTPpacket();
}

std::optional<shs::lib::Color::RgbManagerLayer::effect_id_t> shs::lib::Color::RgbManagerLayerApi::handle(shs::ByteCollectorReadIterator<>& it, std::shared_ptr<RgbManagerLayer> layer)
{
    switch (static_cast<Commands>(it.read()))
    {
        case Commands::ENABLE_BRIGHT_SMOOTH: layer->enableBrightSmooth(); break;
        case Commands::DISABLE_BRIGHT_SMOOTH: layer->disableBrightSmooth(); break;
        case Commands::ENABLE_FADE: layer->enableFade(); break;
        case Commands::DISABLE_FADE: layer->disableFade(); break;
        case Commands::REMOVE_EFFECT: layer->removeEffect(it.get<RgbManagerLayer::effect_id_t>()); break;
        case Commands::CLEAR_EFFECTS: layer->clearEffects(); break;
        case Commands::PUSH_EFFECT:
            {
                RgbManagerLayer::effect_id_t pushed_effect_id{};

                switch (static_cast<RgbEffectType>(it.read()))
                {
                    case RgbEffectType::WHEEL1530:
                        {
                            pushed_effect_id = layer->pushEffect(std::make_unique<Wheel1530Effect>(it.get<shs::t::shs_time_t>(), it.get<Wheel1530>()));
                        }
                        break;
                    case RgbEffectType::FIRE:
                        {
                            pushed_effect_id = layer->pushEffect(std::make_unique<FireRgbEffect>(
                                it.read(),                                      // start hue
                                it.read(),                                      // hue gap
                                it.get<shs::t::shs_fixed_t>(),                  // smooth k
                                it.get<shs::t::shs_time_t>(),                   // duration
                                it.read(), it.read(), it.read(), it.read()      // min and max brightness and saturation
                            ));
                        }
                        break;

                    default: return shs::DTPpacket(); break;
                }

                return pushed_effect_id;
            }
            break;
        case Commands::POP_EFFECT:
            {
                auto id = layer->popEffect();

                return std::make_optional(id);
            }
            break;
        default: break;
    }
    return std::nullopt;
}

shs::DTPpacket shs::lib::Color::RgbManagerLayerApi::m_createAnswerId(Commands command, RgbManagerLayer::effect_id_t id, shs::ByteCollectorReadIterator<>& it) const
{
    shs::ByteCollector<> bc(1 + sizeof(id));
    bc.push_back(command, 1);
    bc.push_back(id);

    return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
}
