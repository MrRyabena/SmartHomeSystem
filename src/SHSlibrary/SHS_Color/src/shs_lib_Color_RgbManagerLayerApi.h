#pragma once

#include <memory>
#include <optional>

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>

#include "shs_lib_Color_RgbManagerLayerInterface.h"
#include "shs_lib_Color_RgbManagerLayerApiCommands.h"


namespace shs::lib::Color
{
    class RgbManagerLayerApi;
}


class shs::lib::Color::RgbManagerLayerApi : public shs::API
{
public:
    using Commands = RgbManagerLayerApiCommands;

    RgbManagerLayerApi(std::shared_ptr<RgbManagerLayerInterface> layer, shs::t::shs_ID_t id);

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    [[nodiscard]] static std::optional<RgbManagerLayerInterface::effect_id_t> handle(shs::ByteCollectorReadIterator<>& it,
        std::shared_ptr<RgbManagerLayerInterface> layer);

protected:
    std::shared_ptr<RgbManagerLayerInterface> m_layer;

    [[nodiscard]] shs::DTPpacket m_createAnswerId(Commands command, RgbManagerLayerInterface::effect_id_t id, shs::ByteCollectorReadIterator<>& it) const;
};
