#pragma once


#include "shs_API.h"
#include "shs_API_reservedID.h"
#include "shs_types.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"

#include <stdint.h>
#include <memory>


namespace shs
{
    class DTP_APIhandler;
    class DTP_APIpackets;
}


shs::DTP_APIhandler : public shs::API
{
public:
    DTP_APIhandler(const shs::t::shs_ID_t ID) API(ID) {}
    ~DTP_APIhandler() = default;

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

};


shs::DTP_APIpackets
{
public:
    static constexpr auto dtp_api_ID = shs::API_reservedID::DTP;

    static shs::DTPpacket getInitialPacket(shs::t::shs_ID_t ID)
    {
        shs::ByteCollector<bc> bc;
        ID.setAPI(dtp_api_ID);
        shs::DTPpacket packet(API_ID, 0, bc);
        packet.set_DTPcode(shs::DTPpacket::INITIAL);

        return std::move(packet);
    }
};
