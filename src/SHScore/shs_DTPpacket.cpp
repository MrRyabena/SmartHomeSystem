#include "shs_DTPpacket.h"

/*
  ----------------------------------------
  DTPpacket
  ----------------------------------------
*/
shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, shs::ByteCollector<>&& data)
    : bc(std::move(data))
{
    uint8_t size = bc.size();
    bc.reserve(1);
    bc.reserve_front(DTP_OFFSETbeg);

    // note: reversed order
    bc.push_front(recipientID);
    bc.push_front(senderID);
    bc.push_front(size + DTP_OFFSETbeg + 1, 1);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const uint8_t* data, const uint8_t size)
    : bc(size + DTP_OFFSETbeg + 1)
{
    bc.push_back(size + DTP_OFFSETbeg + 1, 1);
    bc.push_back(senderID);
    bc.push_back(recipientID);

    bc.write(data, size);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}

uint8_t shs::DTPpacket::check(shs::ByteCollectorReadIterator<>& it)
{
    if (it.size() < it[0]) return Error::size_less;
    if (it.size() > bc[0]) return Error::size_bigger;

    if (it[it[0] - 1] != shs::CRC8::crcBuf(it.begin(), it[0] - 1)) return Error::invalid_crc;

    return Error::ok;
}

uint8_t shs::DTPpacket::check() const
{
    if (bc.size() < bc[0]) return Error::size_less;
    if (bc.size() > bc[0]) return Error::size_bigger;

    if (bc[bc[0] - 1] != shs::CRC8::crcBuf(bc.getPtr(), bc[0] - 1)) return Error::invalid_crc;

    return Error::ok;
}

