#include "shs_DTP_API.h"

#include "shs_APIids.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"

shs::DTP_API::DTP_API(shs::t::shs_ID_t ID) : API(ID.setComponentID(shs::constants::APIids::DTP)) {}

shs::DTPpacket shs::DTP_API::handle(shs::ByteCollectorReadIterator<>& it)
{
    return static_handle(it);
}

shs::DTPpacket shs::DTP_API::static_handle(shs::ByteCollectorReadIterator<>& it)
{
    switch (shs::DTPpacket::get_DTPcode(it))
    {
        case shs::DTPpacket::INITIAL: return shs::DTP_API::getInitialAnswerPacket(shs::DTPpacket::get_recipientID(it)); break;
        case shs::DTPpacket::INITIAL_ANSWER: break;
        case shs::DTPpacket::CONNECTION_REQUEST: return shs::DTP_API::getConnectionRequestAnswerPacket(shs::DTPpacket::get_recipientID(it)); break;
        case shs::DTPpacket::CONNECTION_REQUEST_ANSWER: break;
        default: break;
    }

    return {};
}

shs::DTPpacket shs::DTP_API::getInitialPacket(shs::t::shs_ID_t ID)
{
    ID.setComponentID(static_cast<uint16_t>(shs::constants::APIids::DTP));
    shs::ByteCollector<> bc(1);
    bc.push_back(0, 1);
    shs::DTPpacket packet(ID, 0, std::move(bc));
    packet.set_DTPcode(shs::DTPpacket::INITIAL);

    return packet;
}


shs::DTPpacket shs::DTP_API::getInitialAnswerPacket(shs::t::shs_ID_t ID, bool success)
{
    shs::ByteCollector<> bc(1);
    bc.push_back(success, 1);

    shs::DTPpacket packet(ID, 0, std::move(bc));
    packet.set_DTPcode(shs::DTPpacket::INITIAL_ANSWER);

    return packet;
}


shs::DTPpacket shs::DTP_API::getConnectionRequestPacket(shs::t::shs_ID_t ID)
{
    ID.setComponentID(static_cast<uint16_t>(shs::constants::APIids::DTP));
    shs::ByteCollector<> bc(1);
    bc.push_back(0, 1);
    shs::DTPpacket packet(ID, 0, std::move(bc));
    packet.set_DTPcode(shs::DTPpacket::CONNECTION_REQUEST);

    return packet;
}


shs::DTPpacket shs::DTP_API::getConnectionRequestAnswerPacket(shs::t::shs_ID_t ID, bool success)
{
    shs::ByteCollector<> bc(1);
    bc.push_back(success, 1);

    shs::DTPpacket packet(ID, 0, std::move(bc));
    packet.set_DTPcode(shs::DTPpacket::CONNECTION_REQUEST_ANSWER);

    return packet;
}
