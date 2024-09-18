#include "SHSdtp.h"
#include "shs_DTP.h"

/*
  ----------------------------------------
  DTPpacker
  ----------------------------------------
*/


uint8_t shs::DTPpacker::packDTP(const uint8_t* data, const uint8_t size, const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID)
{
    shs::ByteCollector bc(size + DTP_OFFSETbeg + 1);

    bc.push_back(size + DTP_OFFSETbeg + 1, 1);
    bc.push_back(senderID);
    bc.push_back(recipientID);
    bc.write(data, size);
    bc.push_back(shs::CRC8::crcBuf(bc.getPtr(), bc.size()), 1);

    return bc.buf[0];
}

uint8_t shs::DTPpacker::checkDTP(const shs::ByteCollector<>* bc)
{
    if (bc->size() < bc->buf[0]) return Error::size_less;
    if (bc->size() > bc->buf[0]) return Error::size_bigger;

    if ((*bc)[(*bc)[0] - 1] != shs::CRC8::crcBuf(bc->getPtr(), (*bc)[0] - 1))
        return Error::invalid_crc;

    return Error::ok;
}

uint8_t shs::DTPpacker::parseDTP(shs::ByteCollector<>&& bc, shs::DTPpacket& packet)
{
    auto status = checkDTP(bc);
    if (status) return status;

    bc.get(packet.datasize, 1);
    bc.get(packet.senderID);
    bc.get(packet.recipientID);

    packet.datasize -= DTP_OFFSETbeg + 1;
    packet.bc = std::move(bc);

    return Error::ok;
}

/*
  ----------------------------------------
  DTP
  ----------------------------------------
*/

shs::DTP::DTP(Stream* bus, const shs::settings::shs_ModuleID_t ID) : m_bus(bus), m_ID(ID) {}

shs::DTP::~DTP() {}

uint8_t shs::DTP::tick()
{
    checkBus();
    return 0;
}

uint8_t shs::DTP::checkBus(uint8_t* len)
{
    if (!m_bus)
        return 0;
    if (len)
        m_len = *len;

    if (m_bus->available() > 0)
        if (!m_len)
            m_len = m_bus->read();
    if (len)
        *len = m_len;
    if (!m_len)
        return 0;

    if (m_len && m_bus->available() < m_len - 1)
        return 1;

    shs::ByteCollector col(m_len);
    *(col.ptr++) = m_len;

    for (uint8_t i = 0; i < m_len - 1; i++)
        *(col.ptr++) = m_bus->read();
    m_len = 0;
    if (len)
        *len = 0;

    // shs::DTPdata data;
    // uint8_t size = parseDTP(&col, data);

    handler(col);

    return col.size();
}

uint8_t shs::DTP::sendPacket(shs::ByteCollector* bc, const shs::settings::shs_ModuleID_t to)
{
    return shs::DTP::sendPacket(bc, to, m_ID, m_ID);
}

uint8_t shs::DTP::sendPacket(shs::ByteCollector* bc, const shs::settings::shs_ModuleID_t to,
    const shs::settings::shs_ID_t api_ID, const shs::settings::shs_ModuleID_t from)
{
    packDTP(bc, to, api_ID, from);
    return m_bus->write(bc->buf, bc->buf[0]);
}

