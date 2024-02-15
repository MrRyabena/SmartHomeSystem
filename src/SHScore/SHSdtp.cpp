#include "SHSdtp.h"

shs::DTP::DTP(Stream *bus, void (*handler)(shs::DTPdata &))
{
    _bus = bus;
    _handler = handler;
};

shs::DTP::~DTP()
{
}

uint8_t shs::DTP::tick()
{
    checkBus();
    return 0;
}

uint8_t shs::DTP::checkBus()
{
    if (_bus->available())
        if (!_len)
            _len = _bus->read();
    if (_bus->available() < _len - 1)
        return 1;

    shs::ByteCollector col(_len);
    *(col.ptr++) = (uint8_t *)&_len;
    for (uint8_t i = 0; i < _len - 1; i++)
        *(col.ptr++) = _bus->read();
    _len = 0;

    return parseDTP(&col);
}

uint8_t shs::DTP::sendPacket(shs::ByteCollector *bc, const uint8_t to)
{
    return shs::DTP::sendPacket(bc, to, 0);
}

uint8_t shs::DTP::sendPacket(shs::ByteCollector *bc, const uint8_t to, const uint8_t from)
{
    packDTP(bc, to);
    return : _bus->write(bc->buf, bc.buf[0]);
}

uint8_t shs::DTP::packDTP(shs::ByteCollector *bc, const uint8_t to)
{
    return packDTP(bc, to, _ID);
}

uint8_t shs::DTP::packDTP(shs::ByteCollector *bc, const uint8_t to, const uint8_t from)
{
    bc->reserveBefore(3);
    bc->buf[1] = to;
    bc->buf[2] = from;
    bc->buf[0] = bc->size() + 1;
    bc->add(shs::crc_8(bc->buf, bc->size()), 1);

    return bc->buf[0];
}

uint8_t shs::DTP::checkDTP(shs::ByteCollector *bc)
{
    if (bc->size() < bc->buf[0] - 1)
        return 2;
    if (bc->size() > bc->buf[0])
        return 3;

    uint16_t crc = shs::crc_8(bc->buf, bc->buf[0] - 1);
    if (bc->buf[bc->buf[0] - 1] != crc)
        return 4;
    return 0;
}

uint8_t shs::DTP::parseDTP(shs::ByteCollector *bc)
{
    uint8_t status = checkDTP(bc);
    if (status)
        return status;

    shs::DTPdata data{};
    data.from = bc->buf[2];
    data.to = bc->buf[1];
    data.datasize = bc->size() - DTP_OFFSETbeg - 1;
    bc->readPtr = bc->buf + DTP_OFFSETbeg;
    data.data = bc;

    if (_handler != nullptr)
        _handler(data);
    return 0;
}
