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

#include <stdint.h>
#include <memory>

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


namespace shs
{
    class DTPbus;
};


class shs::DTPbus : public shs::Process
{
public:

    explicit DTPbus(const shs::t::shs_ID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : busID(busID), m_handler(handler), m_len(0), m_tmr(0), m_bc(bufsize)
    {}

    DTPbus(DTPbus&& other) : busID(other.busID), m_handler(other.m_handler),
        m_len(other.m_len), m_tmr(other.m_tmr), m_bc(std::move(other.m_bc))
    {
        other.busID = {};
        other.m_len = {};
        other.m_tmr = {};
    }

    virtual ~DTPbus() = default;

    enum Status : uint8_t { no_data, packet_is_expected, packet_received, packet_processed, invalid_recipient };

    void start() override = 0;
    void tick() override = 0;
    void stop() override = 0;

    virtual Status  processBus() = 0;
    template <class Bus> Status checkBus(Bus& bus);
    template <class Bus> static inline Status checkBus(Bus& bus, shs::ByteCollector<>& buf, uint8_t& len);
    inline Status processPacket();

    virtual uint8_t sendPacket(shs::DTPpacket& packet) = 0;
    virtual uint8_t sendRAW(shs::ByteCollector<>& bc) = 0;
    virtual uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) = 0;
    virtual uint8_t sendRAW(const uint8_t* data, const uint8_t size) = 0;

    void setHandler(shs::API* handler) { m_handler = handler; }

    shs::ByteCollectorReadIterator<> getLastData() { return m_bc.getReadIt(); }


    bool operator<(const shs::DTPbus& other) const { return busID < other.busID; }
    bool operator>(const shs::DTPbus& other) const { return busID > other.busID; }
    bool operator==(const shs::DTPbus& other) const { return busID == other.busID; }
    bool operator!=(const shs::DTPbus& other) const { return busID != other.busID; }


    shs::t::shs_ID_t busID;
    Status status;

protected:

    uint8_t m_len;
    shs::ByteCollector<> m_bc;
    uint32_t m_tmr;
    shs::API* m_handler;
};


template <class Bus>
shs::DTPbus::Status shs::DTPbus::checkBus(Bus& bus)
{
    if (bus.available() == 0) { return Status::no_data; }

    if (m_len == 0) m_len = bus.read();
    if (bus.available() < m_len - 1) { status = Status::packet_is_expected; return status; }

    m_bc.reset();
    m_bc.push_back(m_len, 1);

    for (uint8_t i = 0; i < m_len - 1; i++) m_bc.push_back(bus.read(), 1);

    m_len = 0;

    status = Status::packet_received;
    return status;
}

template <class Bus>
shs::DTPbus::Status shs::DTPbus::checkBus(Bus& bus, shs::ByteCollector& buf, uint8_t& len)
{
    if (bus.available() == 0) { return Status::no_data; }

    if (len == 0) len = bus.read();
    if (bus.available() < len - 1) { status = Status::packet_is_expected; return status; }

    buf.reset();
    buf.push_back(len, 1);

    for (uint8_t i = 0; i < len - 1; i++) buf.push_back(bus.read(), 1);

    len = 0;

    status = Status::packet_received;
    return status;
}


void shs::DTPbus::processPacket()
{
    if (status != packet_received) return no_data;
    auto it = m_bc.getReadIt();
    // DTPhandler ...

    if (m_handler)
    {
        auto output = m_handler->handle(it);
        if (!output.empty()) sendPacket(output);
    }

    return Status::packet_processed;
}
