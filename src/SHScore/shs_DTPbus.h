#pragma once

#include <stdint.h>


#include "shs_settings_private.h"

#ifdef SHS_SF_AVR
#include <shs_lib_AVR_STD_memory.h>
#else
#include <memory>
#endif 


#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#endif


#include "shs_types.h"
#include "shs_ByteCollector.h"
#include "shs_ID.h"
#include "shs_Process.h"
#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_ProgramTimer.h"
#include "shs_DTP_API.h"

#include "shs_debug.h"


namespace shs
{
    class DTPbus;
}


/**
 * @brief Abstract DTP transport bus that receives, processes, and sends packets.
 */
class shs::DTPbus : public shs::Process
{
public:

    enum Status : uint8_t { no_data, packet_is_expected, packet_received, packet_processed, invalid_recipient, bus_error, receive_timeout_error };
    static constexpr auto RECEIVE_TIMEOUT = 10'000;  // ms

    /**
     * @brief Creates a bus wrapper with an optional handler and buffer size.
        * @param busID Bus identifier, must be unique among buses connected to the same DTP instance.
        * @param handler Optional API handler for incoming packets.
        * @param bufsize Size of internal byte buffer (buffer size can be adjusted automatically).
     */
    explicit DTPbus(const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : busID(busID), m_handler(handler), m_len(0), m_receive_timer(RECEIVE_TIMEOUT), m_bc(bufsize)
    {}

    /**
     * @brief Moves a bus wrapper.
     */
    DTPbus(DTPbus&& other) : busID(other.busID), m_handler(other.m_handler),
        m_len(other.m_len), m_receive_timer(other.m_receive_timer), m_bc(std::move(other.m_bc))
    {
        other.busID = {};
        other.m_len = {};
    }

    /**
     * @brief Destroys the bus wrapper.
     */
    virtual ~DTPbus() = default;


    /**
     * @brief Replaces the packet handler.
        * @param handler New handler pointer.
     * @note Old handler will be lost.
     */
    void setHandler(shs::API* handler) { m_handler = handler; }

    /**
     * @brief Reports whether the concrete bus is active.
        * @return True when bus is active.
     */
    virtual bool isActive() const = 0;

    /**
     * @brief Polls the concrete bus for new data.
        * @return Current bus status after polling.
     */
    virtual Status checkBus() = 0;
    /**
     * @brief Polls a bus instance using the shared buffer.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to poll.
        * @return Current bus status after polling.
     */
    template <class Bus> Status checkBus(Bus& bus) { status = checkBus(bus, m_bc, m_len, m_receive_timer, m_handler); return status; }  // sendPacket(m_DTPhandler());
    /**
     * @brief Polls a bus and stores incoming bytes in the given buffer.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to poll.
        * @param buf Buffer used to store incoming bytes.
        * @param len Expected packet length cache.
        * @param receive_timer Timer for tracking receive time.
        * @param handler Optional packet handler.
        * @return Current bus status after polling and optional processing.
     */
    template <class Bus> inline static Status checkBus(Bus& bus, ByteCollector<>& buf, uint8_t& len, shs::ProgramTimer& receive_timer, shs::API* handler = nullptr);

    /**
     * @brief Processes a bus instance using the shared buffer.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @return Current bus status after processing.
     */
    template <class Bus> Status processBus(Bus& bus) { status = processBus(bus, m_bc, m_len); return status; }
    /**
     * @brief Processes a bus and fills a byte collector with the received packet.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @param buf Output packet buffer.
        * @param len Expected packet length cache.
        * @param receive_timer Timer for tracking receive time.
        * @return Processing status.
     */
    template <class Bus> inline static Status processBus(Bus& bus, shs::ByteCollector<>& buf, uint8_t& len, shs::ProgramTimer& receive_timer);

    /**
     * @brief Sends the current buffered packet to the handler.
        * @param handler API handler for packet processing.
        * @return Updated bus status.
     */
    Status processPacket(shs::API& handler) { sendPacket(processPacket(m_bc, handler, status)); return status; }
    /**
     * @brief Decodes buffered data and passes it to the handler.
        * @param data Buffered packet bytes.
        * @param handler API handler to invoke.
        * @param status Input/output status value.
        * @return Handler response packet or empty packet.
     */
    inline static shs::DTPpacket processPacket(shs::ByteCollector<>& data, shs::API& handler, Status& status);

    /**
     * @brief Returns the latest buffered bytes.
        * @return Read iterator for the latest buffered packet.
     */
    shs::ByteCollectorReadIterator<> getLastData() { return m_bc.getReadIt(); }


    /**
     * @brief Sends a packet through the concrete bus.
        * @param packet Packet to send.
        * @return Number of sent bytes.
     */
    virtual uint8_t sendPacket(const shs::DTPpacket& packet) = 0;
    /**
     * @brief Sends a byte collector through the concrete bus.
        * @param bc payload to send.
        * @return Number of sent bytes.
     */
    virtual uint8_t sendRAW(shs::ByteCollector<>& bc) = 0;
    /**
     * @brief Sends bytes from a read iterator through the concrete bus.
        * @param it Iterator over bytes to send.
        * @return Number of sent bytes.
     */
    virtual uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) = 0;
    /**
     * @brief Sends a raw buffer through the concrete bus.
        * @param data Pointer to bytes to send.
        * @param size Number of bytes to send.
        * @return Number of sent bytes.
     */
    virtual uint8_t sendRAW(const uint8_t* data, const uint8_t size) = 0;

    /**
     * @brief Sends a packet through a concrete bus object.
     * @tparam Bus Concrete bus type.
     * @param bus Bus instance used for write operation.
     * @param packet Packet to send.
     * @return Number of sent bytes.
     */
    template <class Bus> static uint8_t sendPacket(Bus& bus, const shs::DTPpacket& packet) { return (packet.empty() ? 0 : bus.write(packet.bc.getPtr(), packet.bc.size())); }
    /**
     * @brief Sends a byte collector through a concrete bus object.
     * @tparam Bus Concrete bus type.
     * @param bus Bus instance used for write operation.
     * @param bc Byte collector to send.
     * @return Number of sent bytes.
     */
    template <class Bus> static uint8_t sendRAW(Bus& bus, shs::ByteCollector<>& bc) { return bus.write(bc.getPtr(), bc.size()); };
    /**
     * @brief Sends iterator bytes through a concrete bus object.
     * @tparam Bus Concrete bus type.
     * @param bus Bus instance used for write operation.
     * @param it Read iterator over bytes to send.
     * @return Number of sent bytes.
     */
    template <class Bus> static uint8_t sendRAW(Bus& bus, shs::ByteCollectorReadIterator<>& it) { return bus.write(it.getPtr(), it.size()); };
    /**
     * @brief Sends a raw byte buffer through a concrete bus object.
     * @tparam Bus Concrete bus type.
     * @param bus Bus instance used for write operation.
     * @param data Pointer to bytes to send.
     * @param size Number of bytes to send.
     * @return Number of sent bytes.
     */
    template <class Bus> static uint8_t sendRAW(Bus& bus, const uint8_t* data, const uint8_t size) { return bus.write(data, size); };

    /**
     * @brief Starts the bus implementation.
     */
    void start() override = 0;
    void tick() override = 0;
    /**
     * @brief Stops the bus implementation.
     */
    void stop() override = 0;


    bool operator<(const shs::DTPbus& other) const { return busID < other.busID; }
    bool operator>(const shs::DTPbus& other) const { return busID > other.busID; }
    bool operator==(const shs::DTPbus& other) const { return busID == other.busID; }
    bool operator!=(const shs::DTPbus& other) const { return busID != other.busID; }


    shs::t::shs_busID_t busID;
    Status status;
#ifndef SHS_SF_AVR                                // TODO: add realization for AVR
    shs::SortedBuf<uint8_t> connected_modules;
#endif
protected:
    shs::ByteCollector<> m_bc;
    shs::API* m_handler;
    shs::ProgramTimer m_receive_timer;
    uint8_t m_len;

    inline shs::DTPpacket m_DTPhandler();
};


template<class Bus>
shs::DTPbus::Status shs::DTPbus::checkBus(Bus& bus, ByteCollector<>& buf, uint8_t& len, shs::ProgramTimer& receive_timer, shs::API* handler)
{
    Status status = processBus(bus, buf, len, receive_timer);

    if (handler) processPacket(buf, *handler, status);

    return status;
}


template <class Bus>
shs::DTPbus::Status shs::DTPbus::processBus(Bus& bus, shs::ByteCollector<>& buf, uint8_t& len, shs::ProgramTimer& receive_timer)
{
    if (bus.available() == 0) { return Status::no_data; }

    if (len == 0)
    {
        len = bus.read();
        receive_timer.reset();

        if (len < 2) { return Status::invalid_recipient; }
    }
    if (receive_timer.expired())
    {
        len = 0;
        while (bus.available()) bus.read();  // clear bus
        return Status::receive_timeout_error;
    }
    if (bus.available() < len - 1) { return Status::packet_is_expected; }

    buf.reset();
    buf.push_back(len, 1);

    for (uint8_t i = 0; i < len - 1; i++) buf.push_back(bus.read(), 1);
    len = 0;

    return Status::packet_received;
}


shs::DTPpacket shs::DTPbus::processPacket(shs::ByteCollector<>& data, shs::API& handler, Status& status)
{
    if (status != packet_received && status != packet_processed) return shs::DTPpacket();

    auto it = data.getReadIt();

    status = Status::packet_processed;
    return handler.handle(it);
}


shs::DTPpacket shs::DTPbus::m_DTPhandler()
{
#ifndef SHS_SF_AVR     

    auto it = getLastData();                              // TODO: add realization for AVR

    switch (shs::DTPpacket::get_DTPcode(it))
    {
        case shs::DTPpacket::INITIAL: connected_modules.attach(shs::DTPpacket::get_senderID(it).getModuleID()); return shs::DTP_APIpackets::getInitialAnswerPacket(shs::DTPpacket::get_recipientID(it).getModuleID(), true); break;
        case shs::DTPpacket::INITIAL_ANSWER: connected_modules.attach(shs::DTPpacket::get_senderID(it).getModuleID()); break;
        case shs::DTPpacket::DEINITIAL: connected_modules.detach(shs::DTPpacket::get_senderID(it).getModuleID()); break;
        default: break;
    }
#endif
    return shs::DTPpacket();
}
