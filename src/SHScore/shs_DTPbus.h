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
#else
#define DEBUG(value)
#pragma message "Used shs::Stream"
#include "shs_Stream.h"
using Stream = shs::Stream;

#endif

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_ByteCollector.h"
#include "shs_ID.h"
#include "shs_Process.h"
#include "shs_API.h"

#include <stdint.h>


namespace shs
{
    class DTPbus;
};


class shs::DTPbus : public shs::Process
{
public:
    explicit DTPbus(Stream& bus, shs::API& handler, const shs::t::shs_ID_t ID, const uint8_t bufsize = 25)
        : m_bus(bus), m_handler(handler), m_ID(ID), m_len(0), m_tmr(0), m_bc(bufsize)
    {}

    ~DTPbus() = default;


    void start() override {}
    void tick() override { checkBus(); }
    void stop() override {}

    uint8_t checkBus();
    uint8_t sendPacket(shs::DTPpacket& packet) { return m_bus.write(packet.bc.getPtr(), packet.bc.size()); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) { return m_bus.write(bc.getPtr(), bc.size()); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) { return m_bus.write(data, size); }

    enum Status : uint8_t { no_data, packet_is_expected, packet_processed, invalid_recipient };

private:
    Stream& m_bus;
    shs::API& m_handler;

    shs::t::shs_ID_t m_ID;

    shs::ByteCollector<> m_bc;
    uint8_t m_len;
    uint32_t m_tmr;

};
