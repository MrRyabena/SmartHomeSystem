#pragma once

#include <memory>

#include <shs_API.h>
#include <shs_DTP.h>
#include <shs_types.h>
#include <shs_ByteCollector.h>

#include "shs_lib_Color_RgbManager.h"
#include "shs_lib_Color_RgbManagerApiCommands.h"
#include "shs_lib_Color_RgbManagerLayerApiCommands.h"
#include "shs_lib_Color_RgbManagerLayerInterface.h"

namespace shs::lib::Color
{
    class RgbManagerVirtual;
}


class shs::lib::Color::RgbManagerVirtual : public shs::lib::Color::RgbManager, public shs::API
{
public:
    using Commands = RgbManagerApiCommands;
    RgbManagerVirtual(std::shared_ptr<shs::DTP> dtp, shs::t::shs_ID_t id, shs::t::shs_ID_t remote_id, std::shared_ptr<RgbController> controller = nullptr);

    void manageLayer(shs::ByteCollector<> buffer, layer_id_t layer_id);
    void manageLayer(RgbManagerLayerApiCommands command, layer_id_t layer_id);

    void setColor(const RGB888 color) override;
    void setBrightness(const uint8_t brightness) override;

    layer_id_t addLayer(std::shared_ptr<RgbManagerLayerInterface> layer) override;
    layer_id_t popLayer() override;
    void removeLayer(const layer_id_t id) override;
    void clearLayers() override;

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override { return shs::DTPpacket{}; }

protected:
    shs::t::shs_ID_t m_remote_id;
    std::shared_ptr<shs::DTP> m_dtp;

    void m_sendCommand(const RgbManagerApiCommands command);
};
