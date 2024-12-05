#pragma once


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
#include "shs_SortedBuf.h"


namespace shs
{
    class DTPbus;
}


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


    // processing incoming data
    virtual Status checkBus() = 0;
    template <class Bus> Status processBus(Bus& bus);
    inline Status processPacket();

    // for additional handlers
    shs::ByteCollectorReadIterator<> getLastData() { return m_bc.getReadIt(); }


    // sending data
    virtual uint8_t sendPacket(const shs::DTPpacket& packet) = 0;
    virtual uint8_t sendRAW(shs::ByteCollector<>& bc) = 0;
    virtual uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) = 0;
    virtual uint8_t sendRAW(const uint8_t* data, const uint8_t size) = 0;


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

    inline void m_DTPhandler(shs::ByteCollectorReadIterator<>& it);
};


template <class Bus>
shs::DTPbus::Status shs::DTPbus::processBus(Bus& bus)
{
    if (bus.available() == 0) { status = Status::no_data; return status; }

    if (m_len == 0) m_len = bus.read();
    if (bus.available() < m_len - 1) { status = Status::packet_is_expected; return status; }

    m_bc.reset();
    m_bc.push_back(m_len, 1);

    for (uint8_t i = 0; i < m_len - 1; i++) m_bc.push_back(bus.read(), 1);

    m_len = 0;

    status = Status::packet_received;
    return status;
}


shs::DTPbus::Status shs::DTPbus::processPacket()
{
    if (status != packet_received) return status;
    auto it = m_bc.getReadIt();

    m_DTPhandler(it);

    if (m_handler)
    {
        auto output = m_handler->handle(it);
        if (!output.empty()) sendPacket(output);
    }

    status = Status::packet_processed;
    return status;
}

#include <shs_debug.h>
void shs::DTPbus::m_DTPhandler(shs::ByteCollectorReadIterator<>& it)
{
    switch (shs::DTPpacket::get_DTPcode(it))
    {
        case shs::DTPpacket::INITIAL: doutln("attach module to bus"); connected_modules.attach(shs::DTPpacket::get_senderID(it).getModuleID()); break;
        case shs::DTPpacket::DEINITIAL: doutln("deattach module to bus"); connected_modules.detach(shs::DTPpacket::get_senderID(it).getModuleID()); break;
        default: break;
    }
}
