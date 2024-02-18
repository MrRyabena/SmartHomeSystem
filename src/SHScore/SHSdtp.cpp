#include "SHSdtp.h"

uint8_t shs::DTPpacker::packDTP(shs::ByteCollector *bc, const uint8_t to, const int16_t apiID)
{
    return packDTP(bc, to, shs::module.config.ID);
}

uint8_t shs::DTPpacker::packDTP(shs::ByteCollector *bc, const uint8_t to, const int16_t apiID, const uint8_t from)
{
    bc->reserveBefore(5);
    bc->buf[1] = to;
    bc->buf[2] = from;
    bc->buf[3] = apiID & 0x000000ff;
    bc->buf[4] = apiID & 0x0000ff00;
    bc->buf[0] = bc->size() + 1;
    bc->add(_crc.crcBuf(bc->buf, bc->size()), 1);

    return bc->buf[0];
}

uint8_t shs::DTPpacker::checkDTP(shs::ByteCollector *bc)
{
    if (bc->size() < bc->buf[0] - 1)
        return 2;
    if (bc->size() > bc->buf[0])
        return 3;

    uint16_t crc = _crc.crcBuf(bc->buf, bc->buf[0] - 1);
    if (bc->buf[bc->buf[0] - 1] != crc)
        return 4;
    return 0;
}

uint8_t shs::DTPpacker::parseDTP(shs::ByteCollector *bc, shs::DTPdata &data)
{
    uint8_t status = checkDTP(bc);
    if (status)
        return status;

    data.from = bc->buf[2];
    data.to = bc->buf[1];
    data.from = bc->buf[3] | ((int16_t)bc->buf[4] << 8);
    data.datasize = bc->size() - shs::settings::DTP_OFFSETbeg - 1;
    bc->readPtr = bc->buf + shs::settigns::DTP_OFFSETbeg;
    data.data = bc;

    return 0;
}

shs::DTP::DTP(Stream *bus) : _bus(bus) {}

shs::DTP::~DTP() {}

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
    *(col.ptr++) = _len;
    for (uint8_t i = 0; i < _len - 1; i++)
        *(col.ptr++) = _bus->read();
    _len = 0;

    shs::DTPdata data;
    uint8_t size = parseDTP(&col, data);

    handler(col);

    return size;
}

uint8_t shs::DTP::sendPacket(shs::ByteCollector *bc, const uint8_t to)
{
    return shs::DTP::sendPacket(bc, to, 0);
}

uint8_t shs::DTP::sendPacket(shs::ByteCollector *bc, const uint8_t to, const uint8_t from)
{
    packDTP(bc, to);
    return _bus->write(bc->buf, bc->buf[0]);
}
