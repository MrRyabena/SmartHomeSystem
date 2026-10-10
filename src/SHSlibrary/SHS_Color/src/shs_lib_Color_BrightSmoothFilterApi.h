#pragma once

#include <memory>

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>

#include "shs_lib_Color_BrightSmoothFilter.h"

namespace shs::lib::Color
{
    class BrightSmoothFilterApi;
}


class shs::lib::Color::BrightSmoothFilterApi : public shs::API
{
public:
    explicit BrightSmoothFilterApi(std::shared_ptr<BrightSmoothFilter> filter, const shs::t::shs_ID_t id);

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    std::shared_ptr<BrightSmoothFilter> m_filter;
};
