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
#include "shs_DTPbusStatus.h"
#include "shs_DTPbusReceiveContext.h"
#include "shs_DTPbusPolicy.h"

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

    using Status = shs::DTPbusStatus;

    /**
     * @brief Creates a bus wrapper with an optional handler and buffer size.
        * @param busID Bus identifier, must be unique among buses connected to the same DTP instance.
        * @param handler Optional API handler for incoming packets.
        * @param policy DTP bus policy.
        * @param bufsize Size of internal byte buffer (buffer size can be adjusted automatically).
     */
    explicit DTPbus(const shs::t::shs_busID_t busID, const shs::DTPbusPolicy policy, shs::API* handler = nullptr, const uint8_t bufsize = DTPbusReceiveContext::DEFAULT_BUFFER_SIZE)
        : busID(busID), m_context(bufsize, handler), m_policy(policy)
    {}

    /**
     * @brief Moves a bus wrapper.
     */
    DTPbus(DTPbus&& other) : busID(other.busID), m_context(std::move(other.m_context))
    {
        other.busID = {};
        other.m_context = {};
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
    void setHandler(shs::API* handler) { m_context.handler = handler; }

    void setReceiveTimeout(const shs::t::shs_time_t timeout) noexcept { m_context.receive_timer.setTimeout(timeout); }
    shs::t::shs_time_t getReceiveTimeout() const { return m_context.receive_timer.getTimeout(); }
    void resetReceiveTimer() noexcept { m_context.receive_timer.reset(); }

    /**
        * @return Number of milliseconds since the last receive.
     */
    shs::t::shs_time_t millisecondsSinceLastReceive() const noexcept { return m_context.receive_timer.milliseconds(); }

    shs::DTPbusPolicy getPolicy() const noexcept { return m_policy; }

    /**
     * @brief Reports whether the concrete bus is active.
        * @return True when bus is active.
     */
    virtual bool isActive() const = 0;

    /**
     * @brief Sets the active state of the concrete bus.
        * @param active New active state.
        * @note May be unworking for some bus implementations, in which case it should be overridden.
     */
    virtual void setActive(const bool active) = 0;

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
    template <class Bus> Status checkBus(Bus& bus) { return checkBus(bus, m_context); }
    /**
     * @brief Polls a bus instance using the specified context.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to poll.
        * @param context Context to use for polling.
        * @return Current bus status after polling.
     */
    template <class Bus>
    static Status checkBus(Bus& bus, shs::DTPbusReceiveContext& context) { return checkBus(bus, context.buffer, context.receive_length, context.receive_timer, context.handler); }
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
    template <class Bus>
    inline static Status checkBus(Bus& bus, ByteCollector<>& buf, uint8_t& len, shs::ProgramTimer& receive_timer, shs::API* handler = nullptr);

    /**
     * @brief Processes a bus instance using the shared buffer.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @return Current bus status after processing.
     */
    template <class Bus>
    Status processBus(Bus& bus) { status = processBus(bus, m_context.buffer, m_context.receive_length); return status; }
    /**
     * @brief Processes a bus instance using the specified context.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @param context Context to use for processing.
        * @return Current bus status after processing.
     */
    template <class Bus>
    inline static Status processBus(Bus& bus, shs::DTPbusReceiveContext& context) { return processBus(bus, context.buffer, context.receive_length, context.receive_timer); }
    /**
     * @brief Processes a bus and fills a byte collector with the received packet.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @param buf Output packet buffer.
        * @param len Expected packet length cache.
        * @param receive_timer Timer for tracking receive time.
        * @return Processing status.
     */
    template <class Bus>
    inline static Status processBus(Bus& bus, shs::ByteCollector<>& buf, uint8_t& len, shs::ProgramTimer& receive_timer);

    /**
     * @brief Sends the current buffered packet to the handler.
        * @param handler API handler for packet processing.
        * @return Updated bus status.
     */
    Status processPacket(shs::API& handler) { sendPacket(processPacket(m_context.buffer, handler, status)); return status; }
    /**
     * @brief Sends the current buffered packet to the handler.
        * @param context Context containing the buffer and handler.
        * @return Updated bus status.
     */
    inline static shs::DTPpacket processPacket(shs::DTPbusReceiveContext& context, Status& status) { return processPacket(context.buffer, *context.handler, status); }
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
    shs::ByteCollectorReadIterator<> getLastData() { return m_context.buffer.getReadIt(); }


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

#ifndef SHS_SF_AVR                                // TODO: add realization for AVR
    shs::SortedBuf<uint8_t> connected_modules;
#endif
    shs::t::shs_busID_t busID;
    Status status;
protected:
    shs::DTPbusPolicy m_policy;
    shs::DTPbusReceiveContext m_context;
    shs::ProgramTime m_last_send_time;

    template <class Bus>
    static inline shs::DTPpacket m_DTPhandler(Bus& bus, shs::ByteCollectorReadIterator<> it);
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

    receive_timer.reset();    // start counting time since last receive

    auto packet = m_DTPhandler(bus, buf.getReadIt());
    if (!packet.empty()) sendPacket(bus, packet);

    return Status::packet_received;
}


shs::DTPpacket shs::DTPbus::processPacket(shs::ByteCollector<>& data, shs::API& handler, Status& status)
{
    if (status != Status::packet_received && status != Status::packet_processed) return shs::DTPpacket();

    auto it = data.getReadIt();

    status = Status::packet_processed;
    return handler.handle(it);
}

template<class Bus>
shs::DTPpacket shs::DTPbus::m_DTPhandler(Bus& bus, shs::ByteCollectorReadIterator<> it)
{
    return shs::DTP_API::static_handle(it);
}
