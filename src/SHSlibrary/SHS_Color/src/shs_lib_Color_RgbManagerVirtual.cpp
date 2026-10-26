#include "shs_lib_Color_RgbManagerVirtual.h"

#include <shs_utils.h>

#include <shs_lib_APIids.h>

#include "shs_lib_Color_RgbControllerApiCommands.h"
#include "shs_lib_Color_RgbManagerApiLayerWrapper.h"


shs::lib::Color::RgbManagerVirtual::RgbManagerVirtual(std::shared_ptr<shs::DTP> dtp, shs::t::shs_ID_t id, shs::t::shs_ID_t remote_id, std::shared_ptr<RgbController> controller)
    : RgbManager(controller),
    shs::API(id.setComponentID(shs::etoi(shs::lib::APIids::COLOR_RGB_MANAGER_API))),
    m_remote_id(remote_id.setComponentID(shs::etoi(shs::lib::APIids::COLOR_RGB_MANAGER_API))),
    m_dtp(dtp)
{}

void shs::lib::Color::RgbManagerVirtual::manageLayer(shs::ByteCollector<> buffer, layer_id_t layer_id)
{
    if (!m_dtp) return;
    buffer.reserve_front(2);
    buffer.push_front(layer_id);
    buffer.push_front(Commands::MANAGE_LAYER, 1);
    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(buffer)));
}

void shs::lib::Color::RgbManagerVirtual::manageLayer(RgbManagerLayerApiCommands command, layer_id_t layer_id)
{
    if (!m_dtp) return;
    shs::ByteCollector<> buffer(2 + 2);
    buffer.push_back(Commands::MANAGE_LAYER, 1);
    buffer.push_back(layer_id);
    buffer.push_back(command, 1);


    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(buffer)));
}

void shs::lib::Color::RgbManagerVirtual::setColor(const RGB888 color)
{
    if (!m_dtp) return;

    shs::ByteCollector<> bc(1 + sizeof(color));
    bc.push_back(Commands::MANAGE_CONTROLLER, 1);
    bc.push_back(RgbControllerApiCommands::SET_COLOR, 1);
    bc.push_back(color);
    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));
}

void shs::lib::Color::RgbManagerVirtual::setBrightness(const uint8_t brightness)
{
    if (!m_dtp) return;

    shs::ByteCollector<> bc(1 + sizeof(brightness));
    bc.push_back(Commands::MANAGE_CONTROLLER, 1);
    bc.push_back(RgbControllerApiCommands::SET_BRIGHTNESS, 1);
    bc.push_back(brightness);

    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));
}

shs::lib::Color::RgbManager::layer_id_t shs::lib::Color::RgbManagerVirtual::addLayer(std::shared_ptr<RgbManagerLayerInterface> layer)
{
    if (!m_dtp) return 0;

    shs::ByteCollector<> bc(1 + 4 + 2 + 4 + 4);
    bc.push_back(Commands::ADD_LAYER, 1);

    bc.push_back(layer->getBrightSmoothStepTimeout());
    bc.push_back(layer->getBrightSmoothStep(), 1);

    bc.push_back(layer->getFadePeriod());
    bc.push_back(layer->getValue());

    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));

    return RgbManager::addLayer(std::make_shared<RgbManagerApiLayerWrapper>(*this, m_layers.size()));
}

shs::lib::Color::RgbManager::layer_id_t shs::lib::Color::RgbManagerVirtual::popLayer()
{
    m_sendCommand(RgbManagerApiCommands::POP_LAYER);
    return RgbManager::popLayer();
}

void shs::lib::Color::RgbManagerVirtual::removeLayer(const layer_id_t id)
{
    if (!m_dtp) return;
    shs::ByteCollector<> bc(1 + sizeof(id));
    bc.push_back(Commands::REMOVE_LAYER, 1);
    bc.push_back(id);
    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));
    RgbManager::removeLayer(id);
}

void shs::lib::Color::RgbManagerVirtual::clearLayers()
{
    m_sendCommand(RgbManagerApiCommands::CLEAR_LAYERS);
    RgbManager::clearLayers();
}

void shs::lib::Color::RgbManagerVirtual::m_sendCommand(const RgbManagerApiCommands command)
{
    if (!m_dtp) return;
    shs::ByteCollector<> bc(1);
    bc.push_back(command, 1);
    m_dtp->sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));
}
