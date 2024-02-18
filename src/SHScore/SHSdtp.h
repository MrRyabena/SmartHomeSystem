/*
  Smart Home System Data Transmission Protocol

  The idea is taken from https://github.com/GyverLibs/GyverBus

  Warning! It is necessary to include Stream-class befor this file:
  #include <Arduino.h>
  or write your class:
  uint8_t Stream::write(const uint8_t* buf, size_t size);
  uint8_t Stream::read();
  uint8_t Stream::available();

*/

/*
  Last update: v1.1.0
  Versions:
    v1.0.0 — created.
    v1.1.0
      - Divided into two classes.
      - A new type of handlers.
      - Added inheritance from class shs::CallbacksKeeper.
      - Using a new class for CRC.
*/

#pragma once
#include <Arduino.h>
#include "SHSModule.h"
#include <stdint.h>
#include "SHSCallbacksKeeper.h"
#include "SHSCRC.h"
#include "SHSByteCollector.h"

namespace settings
{
#ifndef SILENCE_TIMEOUT
#define SILENCE_TIMEOUT 120000
#endif

#define DTP_OFFSETbeg 5
};

namespace shs
{
    enum DTPcommands : uint8_t;
    struct DTPdata;
    class DTP;
    class DTPpacker;
    typedef void (*DTPhandler_t)(shs::DTPdata &){};

};

enum shs::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

struct shs::DTPdata
{
    uint8_t to{};
    uint8_t from{};
    int16_t apiID{};
    uint8_t datasize{};
    shs::ByteCollector &data{};
};

class shs::DTPpacker
{

public:
    uint8_t packDTP(shs::ByteCollector *bc, const uint8_t to);
    uint8_t packDTP(shs::ByteCollector *bc, const uint8_t to, const uint8_t from);
    uint8_t checkDTP(shs::ByteCollector *bc);
    uint8_t parseDTP(shs::ByteCollector *bc, shs::DTPdata &data);

private:
    shs::CRC8 _crc;
};

class shs::DTP : public shs::DTPpacker, public shs::CallbacksKeeper
{
public:
    explicit DTP(Stream *bus);
    ~DTP();

    inline uint8_t tick();
    uint8_t checkBus();

    inline uint8_t sendPacket(shs::ByteCollector *bc, const uint8_t to);
    uint8_t sendPacket(shs::ByteCollector *bc, uint8_t to, uint8_t from);

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
    uint8_t _len{};
    uint32_t tmr = millis();
};
