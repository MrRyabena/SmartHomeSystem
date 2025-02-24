#pragma once


/*
  Last update: v2.0.0
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
    v2.0.0 — divided into parts, rewritten into an abstract class.
      - Template functions for processing different data buses.
      - Storing the ID of connected modules.
      - Active status.
      - Message processing is divided into stages (separate functions).
*/


#include <stdint.h>
#include <memory>


#include "shs_settings_private.h"

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#endif


#include "shs_types.h"
#include "shs_ByteCollector.h"
#include "shs_ID.h"
#include "shs_Process.h"
#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_DTP_API.h"


namespace shs
{
    class DTPbus;
}


/*
  Component DTP. Abstract class of a data bus that accepts and sends messages.
*/
class shs::DTPbus : public shs::Process
{
public:

    enum Status : uint8_t { no_data, packet_is_expected, packet_received, packet_processed, invalid_recipient };


    explicit DTPbus(const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
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


    void setHandler(shs::API* handler) { m_handler = handler; }

    virtual bool isActive() const = 0;

    // processing incoming data 
    virtual Status checkBus() = 0;
    template <class Bus> Status checkBus(Bus& bus) { status = checkBus(bus, m_bc, m_len, m_handler); return status; }  // sendPacket(m_DTPhandler());
    template <class Bus> inline static Status checkBus(Bus& bus, ByteCollector<>& buf, uint8_t& len, shs::API* handler = nullptr);

    // processing bus
    template <class Bus> Status processBus(Bus& bus) { status = processBus(bus, m_bc, m_len); return status; }
    template <class Bus> inline static Status processBus(Bus& bus, shs::ByteCollector<>& buf, uint8_t& len);

    // processing packet
    Status processPacket(shs::API& handler) { sendPacket(processPacket(m_bc, handler, status)); return status; }
    inline static shs::DTPpacket processPacket(shs::ByteCollector<>& data, shs::API& handler, Status& status);

    // for additional handlers
    shs::ByteCollectorReadIterator<> getLastData() { return m_bc.getReadIt(); }


    // sending data
    virtual uint8_t sendPacket(const shs::DTPpacket& packet) = 0;
    virtual uint8_t sendRAW(shs::ByteCollector<>& bc) = 0;
    virtual uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) = 0;
    virtual uint8_t sendRAW(const uint8_t* data, const uint8_t size) = 0;

    template <class Bus> static uint8_t sendPacket(Bus& bus, const shs::DTPpacket& packet) { return (packet.empty() ? 0 : bus.write(packet.bc.getPtr(), packet.bc.size())); }
    template <class Bus> static uint8_t sendRAW(Bus& bus, shs::ByteCollector<>& bc) { return bus.write(bc.getPtr(), bc.size()); };
    template <class Bus> static uint8_t sendRAW(Bus& bus, shs::ByteCollectorReadIterator<>& it) { return bus.write(it.getPtr(), it.size()); };
    template <class Bus> static uint8_t sendRAW(Bus& bus, const uint8_t* data, const uint8_t size) { return bus.write(data, size); };

    // shs::Process
    void start() override = 0;
    void tick() override = 0;
    void stop() override = 0;


    bool operator<(const shs::DTPbus& other) const { return busID < other.busID; }
    bool operator>(const shs::DTPbus& other) const { return busID > other.busID; }
    bool operator==(const shs::DTPbus& other) const { return busID == other.busID; }
    bool operator!=(const shs::DTPbus& other) const { return busID != other.busID; }


    shs::t::shs_busID_t busID;
    Status status;
    shs::SortedBuf<uint8_t> connected_modules;

protected:
    shs::ByteCollector<> m_bc;
    shs::API* m_handler;
    uint32_t m_tmr;
    uint8_t m_len;

    inline shs::DTPpacket m_DTPhandler();
};


template<class Bus>
shs::DTPbus::Status shs::DTPbus::checkBus(Bus& bus, ByteCollector<>& buf, uint8_t& len, shs::API* handler)
{
    Status status = processBus(bus, buf, len);

    if (handler) processPacket(buf, *handler, status);

    return status;
}


template <class Bus>
shs::DTPbus::Status shs::DTPbus::processBus(Bus& bus, shs::ByteCollector<>& buf, uint8_t& len)
{
    if (bus.available() == 0) return Status::no_data;

    if (len == 0) len = bus.read();
    if (bus.available() < len - 1) return Status::packet_is_expected;

    buf.reset();
    buf.push_back(len, 1);

    for (uint8_t i = 0; i < len - 1; i++) buf.push_back(bus.read(), 1);

    len = 0;

    return Status::packet_received;
}


shs::DTPpacket shs::DTPbus::processPacket(shs::ByteCollector<>& data, shs::API& handler, Status& status)
{
    if (status != packet_received || status != packet_processed) return std::move(shs::DTPpacket());

    auto it = data.getReadIt();

    status = Status::packet_processed;
    return std::move(handler.handle(it));
}


shs::DTPpacket shs::DTPbus::m_DTPhandler()
{
    auto it = getLastData();

    switch (shs::DTPpacket::get_DTPcode(it))
    {
        case shs::DTPpacket::INITIAL: connected_modules.attach(shs::DTPpacket::get_senderID(it).getModuleID()); return shs::DTP_APIpackets::getInitialAnswerPacket(shs::DTPpacket::get_recipientID(it).getModuleID(), true); break;
        case shs::DTPpacket::INITIAL_ANSWER: connected_modules.attach(shs::DTPpacket::get_senderID(it).getModuleID()); break;
        case shs::DTPpacket::DEINITIAL: connected_modules.detach(shs::DTPpacket::get_senderID(it).getModuleID()); break;
        default: break;
    }
    return shs::DTPpacket();
}
