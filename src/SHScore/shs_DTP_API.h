#pragma once


#include <stdint.h>
#include <memory>

#include "shs_API.h"
#include "shs_APIids.h"
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
    DTP_APIhandler(shs::t::shs_ID_t ID) : API(ID.setApiID(shs::constants::APIids::DTP)) {}
    ~DTP_APIhandler() = default;

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
};


class shs::DTP_APIpackets
{
public:
    static constexpr auto DTP_API_ID = shs::constants::APIids::DTP;

    static shs::DTPpacket getInitialPacket(shs::t::shs_ID_t ID)
    {
        ID.setApiID(static_cast<uint16_t>(DTP_API_ID));
        shs::DTPpacket packet(ID, 0, std::move(shs::ByteCollector<>()));
        packet.set_DTPcode(shs::DTPpacket::INITIAL);

        return std::move(packet);
    }

    static shs::DTPpacket getInitialAnswerPacket(shs::t::shs_ID_t ID, bool success)
    {
        shs::ByteCollector<> bc(1);
        bc.push_back(success);

        shs::DTPpacket packet(ID, 0, std::move(bc));
        packet.set_DTPcode(shs::DTPpacket::INITIAL_ANSWER);

        return std::move(packet);
    }
};
