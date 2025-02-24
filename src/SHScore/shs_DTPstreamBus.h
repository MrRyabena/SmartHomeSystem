#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — moved to a separate class.
      - It is not debugged, there are bugs.
      - Support and development is expected in the following versions.
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
#include "shs_DTPbus.h"

#include <stdint.h>


namespace shs
{
    class DTPstreamBus;
}

class shs::DTPstreamBus : public shs::DTPbus
{
public:
    explicit DTPstreamBus(Stream& bus, const shs::t::shs_ID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : m_bus(bus), DTPbus(busID, handler, bufsize)
    {}

    DTPstreamBus(DTPstreamBus&& other) : m_bus(other.m_bus), DTPbus(std::move(other)) {}

    ~DTPstreamBus() = default;

    void start() override {}
    void tick() override {}
    void stop() override {}

    uint8_t checkBus() override { checkBus(m_bus); }
    uint8_t sendPacket(shs::DTPpacket& packet) override { return m_bus.write(packet.bc.getPtr(), packet.bc.size()); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return m_bus.write(bc.getPtr(), bc.size()); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return m_bus.write(it.getPtr(), it.size()); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return m_bus.write(data, size); }

protected:
    Stream& m_bus;
};

