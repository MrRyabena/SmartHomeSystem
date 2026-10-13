#pragma once

#include <memory>

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>

#include "shs_lib_Color_RgbManagerLayer.h"
#include "shs_lib_Color_RgbManagerLayerApiCommands.h"


namespace shs::lib::Color
{
    class RgbManagerLayerApi;
}


class shs::lib::Color::RgbManagerLayerApi : public shs::API
{
public:
    using Commands = RgbManagerLayerApiCommand;

    RgbManagerLayerApi(std::shared_ptr<RgbManagerLayer> layer, const shs::t::shs_ID_t id);

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    std::shared_ptr<RgbManagerLayer> m_layer;

    [[nodiscard]] shs::DTPpacket m_createAnswerId(Commands command, RgbManagerLayer::effect_id_t id, shs::ByteCollectorReadIterator<>& it) const;
};
