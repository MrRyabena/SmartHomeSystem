#pragma once

#include <memory>

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>

#include "shs_lib_Color_RgbManagerApiCommands.h"
#include "shs_lib_Color_RgbManager.h"


namespace shs::lib::Color
{
    class RgbManagerApi;
}


class shs::lib::Color::RgbManagerApi : public shs::API
{
public:
    using Commands = RgbManagerApiCommands;

    explicit RgbManagerApi(std::shared_ptr<RgbManager> manager, shs::t::shs_ID_t id);


    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    std::shared_ptr<RgbManager> m_manager;
};
