#pragma once


#include <stdint.h>
#include <memory>

#include "shs_API.h"
#include "shs_reservedID.h"
#include "shs_types.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"


namespace shs
{
    class DTP_APIhandler;
    class DTP_APIpackets;
}


class shs::DTP_APIhandler : public shs::API
{
public:
    DTP_APIhandler(const shs::t::shs_ID_t ID) : API(ID) {}
    ~DTP_APIhandler() = default;

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
};


class shs::DTP_APIpackets
{
public:
    static constexpr auto dtp_api_ID = shs::ApiIDreserved::DTP;

    static shs::DTPpacket getInitialPacket(shs::t::shs_ID_t ID)
    {
        shs::ByteCollector<> bc;
        ID.setApiID(static_cast<uint16_t>(dtp_api_ID));
        shs::DTPpacket packet(ID, 0, std::move(bc));
        packet.set_DTPcode(shs::DTPpacket::INITIAL);

        return std::move(packet);
    }
};
