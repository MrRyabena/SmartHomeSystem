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

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#define DEBUG(value) ({ Serial.println(value); })

#else
#define DEBUG(value)
#pragma message "Used shs::Stream"
#include "shs_Stream.h"
using Stream = shs::Stream;

#endif

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_CallbacksKeeper.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ID.h"

#include <stdint.h>

namespace shs::settings
{
#ifndef SILENCE_TIMEOUT
#define SILENCE_TIMEOUT 120000
#endif

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

    struct DTPpacket;
    class DTP;
    class DTPpacker;
    typedef void (*DTPhandler_t)(shs::DTPdata&);

};

enum shs::DTPcommands::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

struct shs::DTPpacket
{
    DTPpacket(shs::ByteCollector<>&& bc_data)
        : bc(std::move(bc_data))
    {
        shs::DTPpacker::parseDTP(&bc, *this);
    }
    
    shs::t::shs_ID_t senderID{};
    shs::t::shs_ID_t recipientID{};
    uint8_t datasize{};
    shs::ByteCollector<> bc;

};

/*
  ----------------------------------------
  DTPpacker
  ----------------------------------------
*/

/*
  0x00  1B  -- message size
  0x01  4B  -- sender's ID
  0x05  4B  -- recipient's ID
  0x09
  ....  ..  -- data
  0xXX  1B  -- CRC
*/
class shs::DTPpacker
{
public:

    static uint8_t packDTP(const uint8_t* data, const uint8_t size, const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID);
    static uint8_t checkDTP(const shs::ByteCollector<>* bc);
    uint8_t parseDTP(shs::ByteCollector<>&& bc, shs::DTPpacket& packet);

    static constexpr auto DTP_OFFSETbeg = 10;

    static enum Error : uint8_t
    {
        ok,
        size_less,
        size_bigger,
        invalid_crc
    };

};

/*
  ----------------------------------------
  DTP
  ----------------------------------------
*/
class shs::DTP : public shs::DTPpacker, public shs::CallbacksKeeper
{
public:
    explicit DTP(Stream* bus, const shs::settings::shs_ModuleID_t ID);
    ~DTP();

    uint8_t tick();
    uint8_t checkBus(uint8_t* len = nullptr);

    uint8_t sendPacket(shs::ByteCollector* bc, const shs::settings::shs_ModuleID_t to);
    uint8_t sendPacket(shs::ByteCollector* bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID, const shs::settings::shs_ModuleID_t from);

private:
    Stream* m_bus{};
    uint8_t m_len{};
    uint32_t m_tmr{};
    shs::settings::shs_ModuleID_t m_ID{};
};
