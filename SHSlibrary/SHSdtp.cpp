#include "SHSdtp.h"

shs::DTP::DTP(uint8_t ID, Stream *bus, void (*callback)(shs::DTPdata &))
{
    _ID = ID;
    _bus = bus;
    _callback = callback;
};

shs::DTP::~DTP()
{
}

uint8_t shs::DTP::checkBus(uint8_t *len)
{
    if (_bus->available())
        if (!*len)
            *len = _bus->read();
    if (_bus->available() < *len - 1)
        return 1;
    shs::ByteCollector col(*len);
    *(++col.ptr) = *len;
    for (uint8_t i = 0; i < *len - 1; i++)
        *(++col.ptr) = _bus->read();
    *len = 0;

    return (parseDTP(&col, _callback));
}

uint8_t shs::DTP::packDTP(shs::ByteCollector *bc, uint8_t to)
{
    return packDTP(bc, to, _ID);
}

uint8_t shs::DTP::packDTP(shs::ByteCollector *bc, uint8_t to, uint8_t from)
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

uint8_t shs::DTP::parseDTP(shs::ByteCollector *bc, void (*callback)(shs::DTPdata &))
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

    callback(data);
    return 0;
}
