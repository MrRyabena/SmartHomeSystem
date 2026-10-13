#pragma once

#include <memory>

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>

#include "shs_lib_Color_BrightSmoothFilter.h"
#include "shs_lib_Color_BrightSmoothFilterApiCommands.h"

namespace shs::lib::Color
{
    class BrightSmoothFilterApi;
}


class shs::lib::Color::BrightSmoothFilterApi : public shs::API
{
public:
    using Commands = BrightSmoothFilterApiCommands;

    explicit BrightSmoothFilterApi(std::shared_ptr<BrightSmoothFilter> filter, const shs::t::shs_ID_t id);

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
    
    static void handle(shs::ByteCollectorReadIterator<>& it, std::shared_ptr<BrightSmoothFilter> filter);

protected:
    std::shared_ptr<BrightSmoothFilter> m_filter;
};
