#pragma once

#include <memory>

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>

#include "shs_lib_Color_RgbManager.h"

namespace shs::lib::Color
{
    class RgbManagerApi;
}


class shs::lib::Color::RgbManagerApi : public shs::API
{
public:
    explicit RgbManagerApi(const shs::t::shs_ID_t id);


    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
};
