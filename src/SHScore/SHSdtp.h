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

#ifdef _Arduino_
#include <Arduino.h>
#else
#include "SHSStream.h"
using Stream = shs::Stream;
#endif

#include <stdint.h>
#include "SHSsettings_private.h"
#include "SHSCallbacksKeeper.h"
#include "SHSCRC.h"
#include "SHSByteCollector.h"

namespace shs::settings
{
#ifndef SILENCE_TIMEOUT
#define SILENCE_TIMEOUT 120000
#endif

    inline const uint8_t DTP_OFFSETbeg = 5;
};

namespace shs
{
    enum DTPcommands : uint8_t;
    enum DTPhandlerStatus : uint8_t;
    struct DTPdata;
    class DTP;
    class DTPpacker;
    typedef void (*DTPhandler_t)(shs::DTPdata &);

};

enum shs::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

enum shs::DTPhandlerStatus : uint8_t
{
    PROCESSED,
    INVALIDaddress,
    PTRerror,
    CMDerror,
};

struct shs::DTPdata
{
    shs::settings::shs_ModuleID_t to{};
    shs::settings::shs_ModuleID_t from{};
    shs::settings::shs_ID_t apiID{};
    uint8_t datasize{};
};

class shs::DTPpacker
{

public:
    // uint8_t packDTP(shs::ByteCollector *bc, const uint8_t to, const int16_t apiID);
    uint8_t packDTP(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t apiID, const shs::settings::shs_ModuleID_t from);
    uint8_t checkDTP(shs::ByteCollector *bc);
    uint8_t parseDTP(shs::ByteCollector *bc, shs::DTPdata &data);

protected:
    shs::CRC8 _crc;
};

class shs::DTP : public shs::DTPpacker, public shs::CallbacksKeeper
{
public:
    explicit DTP(Stream *bus, const shs::settings::shs_ModuleID_t ID);
    ~DTP();

    uint8_t tick();
    uint8_t checkBus(uint8_t len = UINT8_MAX);

    uint8_t sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to);
    uint8_t sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID, const shs::settings::shs_ModuleID_t from);

private:
    Stream *_bus{};
    uint8_t _len{};
    uint32_t tmr{};
    shs::settings::shs_ModuleID_t m_ID{};
};
