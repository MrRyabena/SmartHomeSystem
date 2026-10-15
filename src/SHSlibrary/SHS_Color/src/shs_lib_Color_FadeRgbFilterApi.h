#pragma once


#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>

#include "shs_lib_Color_FadeRgbFilter.h"
#include "shs_lib_Color_FadeRgbFilterApiCommands.h"

namespace shs::lib::Color
{
    class FadeRgbFilterApi;
}


class shs::lib::Color::FadeRgbFilterApi : public shs::API
{
public:
    using Commands = FadeRgbEffectApiCommands;

    explicit FadeRgbFilterApi(std::shared_ptr<FadeRgbFilter> filter, shs::t::shs_ID_t id);

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    std::shared_ptr<FadeRgbFilter> m_filter;

};
