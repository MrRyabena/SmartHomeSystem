#include "shs_lib_Color_RgbManagerApi.h"

#include <shs_utils.h>

#include <shs_lib_APIids.h>

#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_BrightSmoothFilter.h"
#include "shs_lib_Color_FadeRgbFilter.h"
#include "shs_lib_Color_RgbManagerLayer.h"
#include "shs_lib_Color_RgbManagerLayerApi.h"
#include "shs_lib_Color_RgbControllerApi.h"
#include "shs_lib_Color_RgbController.h"

shs::lib::Color::RgbManagerApi::RgbManagerApi(std::shared_ptr<RgbManager> manager, shs::t::shs_ID_t id)
    : shs::API(id.setComponentID(shs::etoi(shs::lib::APIids::COLOR_RGB_MANAGER_API))), m_manager(manager)
{}

shs::DTPpacket shs::lib::Color::RgbManagerApi::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));
    switch (static_cast<Commands>(it.read()))
    {
        case Commands::ADD_LAYER:
            {
                // brightness filter
                const BrightSmoothFilter bright_filter(it.get<shs::t::shs_time_t>(), it.read(), it.read());

                // color fade filter
                const FadeRgbFilter fade_filter(it.get<shs::t::shs_time_t>());

                // base color
                const auto base_color = it.get<RGBV8888>();

                // create a new layer
                const auto id = m_manager->addLayer(std::make_shared<RgbManagerLayer>(bright_filter, fade_filter, base_color));

                shs::ByteCollector<> bc(1 + sizeof(id));
                bc.push_back(Commands::LAYER_ADDED_ID, 1);
                bc.push_back(id);
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::REMOVE_LAYER:m_manager->removeLayer(it.read()); break;
        case Commands::POP_LAYER:
            {
                auto result = m_manager->popLayer();
                shs::ByteCollector<> bc(1 + sizeof(result));
                bc.push_back(Commands::LAYER_POPPED_ID, 1);
                bc.push_back(result);
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::MANAGE_LAYER:
            {
                auto layer = m_manager->getLayer(it.get<RgbManager::layer_id_t>());
                if (layer)
                {
                    [[maybe_unused]] auto id = RgbManagerLayerApi::handle(it, layer);
                }
            }
            break;
        case Commands::CLEAR_LAYERS: m_manager->clearLayers(); break;
        case Commands::MANAGE_CONTROLLER:
            {
                RgbControllerApi::handle(it, *reinterpret_cast<RgbController*>(this));
            }
            break;
        default: break;
    }

    return shs::DTPpacket();
}
