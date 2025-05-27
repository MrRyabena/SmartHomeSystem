#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.0.0 — created.
    v2.1.0 — fixed a bug. There is a critical error that has not been fixed yet.
*/

/*
  Classes for working with DTP service data.
*/

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
    DTP_APIhandler(shs::t::shs_ID_t ID) : API(ID.setComponentID(shs::constants::APIids::DTP)) {}
    ~DTP_APIhandler() = default;

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
};


class shs::DTP_APIpackets
{
public:
    static constexpr auto DTP_API_ID = shs::constants::APIids::DTP;

    static shs::DTPpacket getInitialPacket(shs::t::shs_ID_t ID)
    {
        ID.setComponentID(static_cast<uint16_t>(DTP_API_ID));
        shs::ByteCollector<> bc;
        bc.push_back(0);
        shs::DTPpacket packet(ID, 0, std::move(bc));
        packet.set_DTPcode(shs::DTPpacket::INITIAL);

        return packet;
    }

    static shs::DTPpacket getInitialAnswerPacket(shs::t::shs_ID_t ID, bool success)
    {
        shs::ByteCollector<> bc(1);
        bc.push_back(success);

        shs::DTPpacket packet(ID, 0, std::move(bc));
        packet.set_DTPcode(shs::DTPpacket::INITIAL_ANSWER);

        return packet;
    }
};
