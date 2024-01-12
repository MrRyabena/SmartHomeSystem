/*
  Smart Home System Data Transmission Protocol

  Warning! It is necessary to include Stream-class befor this file:
  #include <Arduino.h>
  or write your class:
  size_t Stream:: write(const uint8_t* buf, size_t size);
  uint8_t Stream::read();
  size_t Stream::available();

*/

#pragma once
#include "SHSalgorithm.h"
#include "SHSByteCollector.h"

#define SILENCE_TIMEOUT 120000
#define DTP_OFFSETbeg 3

namespace shs
{
    enum DTPcommands : uint8_t;
    struct DTPdata;
    class DTP;

};

enum shs::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

struct shs::DTPdata
{
    uint8_t from{};
    uint8_t to{};
    uint8_t datasize{};
    shs::ByteCollector *data{};
};

class shs::DTP
{
public:
    DTP(Stream *bus, void (*handler)(shs::DTPdata &));
    ~DTP();

    uint8_t tick();
    uint8_t checkBus();

    uint8_t sendPacket(shs::ByteCollector *bc, const uint8_t to);
    uint8_t sendPacket(shs::ByteCollector *bc, uint8_t to, uint8_t from);

    uint8_t packDTP(shs::ByteCollector *bc, const uint8_t to);
    uint8_t packDTP(shs::ByteCollector *bc, const uint8_t to, const uint8_t from);
    uint8_t checkDTP(shs::ByteCollector *bc);
    uint8_t parseDTP(shs::ByteCollector *bc);

    template <typename T>
    uint8_t sendRAW(const T &data, const uint8_t to)
    {
        uint8_t crc = shs::CRC8_beg;
        uint8_t size = sizeof(T) + DTP_OFFSETbeg + 1;

        shs::crc_8_update(crc, size);
        shs::crc_8_update(crc, to);
        shs::crc_8_update(crc, _ID);

        _bus.write(size);
        _bus.write(to);
        _bus.write(_ID);

        uint8_t *ptr = (uint8_t *)&data;
        for (uint8_t i = 0; i < sizeof(T), i++)
        {
            _bus.write(*ptr);
            crc_8_update(crc, *ptr++);
        }
        _bus.write(crc);
    }

private:
    Stream *_bus{};
    void (*_handler)(shs::DTPdata &){};
    uint8_t _len{};
    uint32_t tmr = millis();
};
