#include "shs_lib_Color_RgbManagerLayerApi.h"

#include "shs_lib_Color_RgbEffectType.h"
#include "shs_lib_Color_Wheel1530Effect.h"
#include "shs_lib_Color_Wheel1530.h"

shs::lib::Color::RgbManagerLayerApi::RgbManagerLayerApi(std::shared_ptr<RgbManagerLayer> layer, const shs::t::shs_ID_t id)
    : m_layer(layer), shs::API(id.setComponentID(shs::APIids::COLOR_RGB_MANAGER_LAYER))
{}

shs::DTPpacket shs::lib::Color::RgbManagerLayerApi::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case Commands::ENABLE_BRIGHT_SMOOTH: m_layer->enableBrightSmooth(); break;
        case Commands::DISABLE_BRIGHT_SMOOTH: m_layer->disableBrightSmooth(); break;
        case Commands::ENABLE_FADE: m_layer->enableFade(); break;
        case Commands::DISABLE_FADE: m_layer->disableFade(); break;
        case Commands::PUSH_EFFECT:
            {
                RgbManagerLayer::effect_id_t pushed_effect_id{};

                switch (static_cast<RgbEffectType>(it.read()))
                {
                    case RgbEffectType::WHEEL1530:
                        {
                            pushed_effect_id = m_layer->pushEffect(std::make_unique<Wheel1530Effect>(it.get<shs::t::shs_time_t>(), it.get<Wheel1530>()));
                        }
                        break;
                    case RgbEffectType::FIRE:
                        {
                            pushed_effect_id = m_layer->pushEffect(std::make_shared<FireEffect>(
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

                return m_createAnswerId(Commands::PUSHED_EFFECT_ID, pushed_effect_id, it);
            }
            break;
        case Commands::POP_EFFECT:
            {
                auto id = m_layer->popEffect();

                return m_createAnswerId(Commands::POPPED_EFFECT_ID, id, it);
            }
            break;
        case Commands::POP_EFFECT:
            {
                auto id = m_layer->popEffect();

                return m_createAnswerId(Commands::POPPED_EFFECT_ID, id, it);
            }
            break;
        case Commands::REMOVE_EFFECT: m_layer->removeEffect(it.get<RgbEffectType>()); break;
        case Commands::CLEAR_EFFECTS: m_layer->clearEffects(); break;

        default: break;
    }

    return shs::DTPpacket();
}

shs::DTPpacket shs::lib::Color::RgbManagerLayerApi::m_createAnswerId(Commands command, RgbManagerLayer::effect_id_t id, shs::ByteCollectorReadIterator<>& it) const
{
    shs::ByteCollector<> bc(1 + sizeof(id));
    bc.push_back(command, 1);
    bc.push_back(id);

    return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
}

