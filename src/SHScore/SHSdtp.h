#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0
      - Divided into two classes.
      - A new type of handlers.
      - Added inheritance from class shs::CallbacksKeeper.
      - Using a new class for CRC.
    v1.0.0 — release.
      - Namespaces added.
      - Variable names have been corrected.
*/

/*
  Smart Home System Data Transmission Protocol

  The idea is taken from https://github.com/GyverLibs/GyverBus
*/

/*
  WARNING! It is necessary to include Stream-class befor this file.
  If the <Arduino.h> is not used, you need to create your own class inherited from
  abstract class shs::Stream (SHSStream.h)
*/

#if __has_include("Arduino.h")
#include <Arduino.h>

#else
#pragma message "Used shs::Stream"
#include "SHSStream.h"
using Stream = shs::Stream;

#endif

#include "SHSsettings_private.h"
#include "SHSCallbacksKeeper.h"
#include "SHSCRC.h"
#include "SHSByteCollector.h"

#include <stdint.h>

namespace shs::settings
{
#ifndef SILENCE_TIMEOUT
#define SILENCE_TIMEOUT 120000
#endif

    inline const uint8_t DTP_OFFSETbeg = 5;
};

namespace shs
{
    namespace DTPcommands
    {
        enum DTPcommands : uint8_t;
    };

    namespace DTPhandlerStatus
    {
        enum DTPhandlerStatus : uint8_t;
    };

    struct DTPdata;
    class DTP;
    class DTPpacker;
    typedef void (*DTPhandler_t)(shs::DTPdata &);

};

enum shs::DTPcommands::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

enum shs::DTPhandlerStatus::DTPhandlerStatus : uint8_t
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

/*
  ----------------------------------------
  DTPpacker
  ----------------------------------------
*/
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

/*
  ----------------------------------------
  DTP
  ----------------------------------------
*/
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
    Stream *m_bus{};
    uint8_t m_len{};
    uint32_t m_tmr{};
    shs::settings::shs_ModuleID_t m_ID{};
};
