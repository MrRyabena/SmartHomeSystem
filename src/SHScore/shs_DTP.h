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
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ID.h"
#include "shs_SortedBuf.h"
#include "shs_Process.h"
#include "shs_API.h"
#include "shs_algorithm.h"
#include "shs_DTPpacket.h"
#include <stdint.h>
#include "functional"

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

    class DTP;

    namespace DTPless
    {
        struct APIptr;
        struct APIid;
    }
};

enum shs::DTPcommands::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};


struct shs::DTPless::APIptr { bool operator()(const shs::API* lhs, const shs::API* rhs) const { return lhs->API_ID < rhs->API_ID; } };
struct shs::DTPless::APIid
{
    bool operator()(const shs::API* lhs, const shs::t::shs_ID_t rhs) const { return lhs->API_ID < rhs; }
    bool operator()(const shs::t::shs_ID_t lhs, const shs::API* rhs) const { return lhs < rhs->API_ID; }
};


/*
  ----------------------------------------
  DTP
  ----------------------------------------
*/
class shs::DTP : public shs::Process, public shs::SortedBuf<shs::API*, shs::DTPless::APIptr>
{
public:
    explicit DTP(Stream& bus, const shs::t::shs_ID_t ID)
        : m_bus(bus), m_ID(ID), m_len(0), m_tmr(0)
    {}

    ~DTP() = default;


    void start() override {}
    void tick() override { checkBus(); }
    void stop() override {}

    uint8_t checkBus();
    uint8_t sendPacket(shs::DTPpacket& packet) { return m_bus.write(packet.bc.getPtr(), packet.bc.size()); }

    enum Status : uint8_t { no_data, packet_is_expected, packet_processed, invalid_recipient };

private:
    uint8_t m_handle_packet(shs::ByteCollector<>&& bc);

    Stream& m_bus;
    uint8_t m_len;
    uint32_t m_tmr;
    shs::t::shs_ID_t m_ID;
};
