#pragma once

#include <memory>

#include <shs_API.h>

#include "shs_lib_Color_RgbControllerApiCommands.h"
#include "shs_lib_Color_RgbController.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_DTPpacket.h"



namespace shs::lib::Color
{
    class RgbControllerApi;
}


class shs::lib::Color::RgbControllerApi : public shs::API
{
public:

    RgbControllerApi(shs::t::shs_ID_t id, std::shared_ptr<RgbController> controller);

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    std::shared_ptr<RgbController> m_controller;
};
