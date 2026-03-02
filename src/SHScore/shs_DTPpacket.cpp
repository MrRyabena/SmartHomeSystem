#include "shs_DTPpacket.h"

/*
  ----------------------------------------
  DTPpacket
  ----------------------------------------
*/
shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, shs::ByteCollector<>&& data) noexcept
    : bc(std::move(data))
{
    uint8_t size = bc.size();
    bc.reserve(1);
    bc.reserve_front(DTPstandard_OFFSETbeg);

    // note: reversed order
    bc.push_front(recipientID);
    bc.push_front(senderID);
    bc.push_front(STANDARD, 1);
    bc.push_front(size + DTPstandard_OFFSETbeg + 1, 1);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const shs::t::shs_ID_t mask, shs::ByteCollector<>&& data) noexcept
    : bc(std::move(data))
{
    auto size = bc.size();
    bc.reserve(1);
    bc.reserve_front(DTPfast_OFFSETbeg + sizeof(mask));

    // note: reversed order
    bc.push_front(mask);
    bc.push_front(recipientID);
    bc.push_front(senderID);
    bc.push_front(MASK, 1);
    bc.push_front(size + DTPstandard_OFFSETbeg + sizeof(mask) + 1, 1);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const shs::ByteCollector<>& data) noexcept
    : bc(data.size() + DTPstandard_OFFSETbeg + 1)
{
    // note: direct order
    bc.push_back(data.size() + DTPstandard_OFFSETbeg + 1, 1);
    bc.push_back(STANDARD, 1);
    bc.push_back(senderID);
    bc.push_back(recipientID);

    for (auto x : data) bc.push_back(x, 1);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const shs::t::shs_ID_t mask, const shs::ByteCollector<>& data) noexcept
    : bc(data.size() + DTPstandard_OFFSETbeg + sizeof(mask) + 1)
{
    // note: direct order
    bc.push_back(data.size() + DTPstandard_OFFSETbeg + sizeof(mask) + 1, 1);
    bc.push_back(MASK, 1);
    bc.push_back(senderID);
    bc.push_back(recipientID);
    bc.push_back(mask);

    for (auto x : data) bc.push_back(x, 1);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const uint8_t* data, const uint8_t size) noexcept
    : bc(size + DTPstandard_OFFSETbeg + 1)
{
    bc.push_back(size + DTPstandard_OFFSETbeg + 1, 1);
    bc.push_back(STANDARD, 1);
    bc.push_back(senderID);
    bc.push_back(recipientID);

    bc.write(data, size);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const shs::t::shs_ID_t mask, const uint8_t* data, const uint8_t size) noexcept
    : bc(size + DTPstandard_OFFSETbeg + sizeof(mask) + 1)
{
    bc.push_back(size + DTPstandard_OFFSETbeg + sizeof(mask) + 1, 1);
    bc.push_back(MASK, 1);
    bc.push_back(senderID);
    bc.push_back(recipientID);
    bc.push_back(mask);

    bc.write(data, size);

    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1), 1);
}


shs::DTPpacket::DTPpacket(const uint8_t* data, const uint8_t size) noexcept
    : bc(size + DTPfast_OFFSETbeg)
{
    bc.push_back(size + DTPstandard_OFFSETbeg, 1);
    bc.push_back(FAST, 1);

    bc.write(data, size);
}


uint8_t shs::DTPpacket::check(shs::ByteCollectorReadIterator<> it)
{
    if (it.size() < it[0]) return Error::size_less;
    if (it.size() > it[0]) return Error::size_bigger;

    if (it.back() != shs::CRC8::crcBuf(it.getPtr(), it[0] - 1)) return Error::invalid_crc;

    return Error::ok;
}

uint8_t shs::DTPpacket::check() const
{
    if (bc.size() < bc[0]) return Error::size_less;
    if (bc.size() > bc[0]) return Error::size_bigger;

    if (bc.back() != shs::CRC8::crcBuf(bc.getPtr(), bc[0] - 1)) return Error::invalid_crc;

    return Error::ok;
}


shs::t::shs_ID_t shs::DTPpacket::get_senderID(shs::ByteCollectorReadIterator<> it)
{
    shs::t::shs_ID_t id{};
    if (get_DTPcode(it) == FAST) return id;

    it.set_position(2);
    it.get(id);

    return id;
}


shs::t::shs_ID_t shs::DTPpacket::get_recipientID(shs::ByteCollectorReadIterator<> it)
{
    shs::t::shs_ID_t id{};
    if (get_DTPcode(it) == FAST) return id;

    it.set_position(2 + sizeof(shs::t::shs_ID_t));
    it.get(id);

    return id;
}


uint8_t shs::DTPpacket::get_datasize(shs::ByteCollectorReadIterator<> it)
{
    uint8_t offset_size{};

    switch (get_DTPcode(it))
    {
        case STANDARD: offset_size = DTPstandard_OFFSETbeg + 1; break;
        case FAST: offset_size = DTPfast_OFFSETbeg; break;
        case MASK: offset_size = DTPstandard_OFFSETbeg + sizeof(shs::t::shs_ID_t) + 1; break;
        default: offset_size = DTPstandard_OFFSETbeg + 1; break;
    }

    return it[0] - offset_size;
}

uint8_t shs::DTPpacket::get_dataBeg(shs::ByteCollectorReadIterator<> it)
{
    switch (get_DTPcode(it))
    {
        case STANDARD: return DTPstandard_OFFSETbeg; break;
        case FAST: return DTPfast_OFFSETbeg; break;
        case MASK: return DTPstandard_OFFSETbeg + sizeof(shs::t::shs_ID_t); break;
        default: return DTPstandard_OFFSETbeg; break;
    }
    return DTPstandard_OFFSETbeg;
}

shs::t::shs_ID_t shs::DTPpacket::get_mask(shs::ByteCollectorReadIterator<> it)
{
    auto dtp_code = get_DTPcode(it);
    if (dtp_code != DTPcode::MASK) return 0;
    it.set_position(0x10);
    shs::t::shs_ID_t mask{};
    it.get(mask);
    return mask;
}


