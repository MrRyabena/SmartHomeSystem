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
#include "shs_DTPbusReceiveStatus.h"
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

    using ReceiveStatus = shs::DTPbusReceiveStatus;

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

    ReceiveStatus getReceiveStatus() const noexcept { return m_context.status; }

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
    virtual ReceiveStatus checkBus() = 0;
    /**
     * @brief Polls a bus instance using the shared buffer.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to poll.
        * @return Current bus status after polling.
     */
    template <class Bus> ReceiveStatus checkBus(Bus& bus) { checkBus(bus, m_context); return m_context.status; }
    /**
     * @brief Polls a bus instance using the specified context.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to poll.
        * @param context Context to use for polling.
        * @return Current bus status after polling.
     */
    template <class Bus>
    static ReceiveStatus checkBus(Bus& bus, shs::DTPbusReceiveContext& context);

    /**
     * @brief Processes a bus instance using the shared buffer.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @return Current bus status after processing.
     */
    template <class Bus>
    inline ReceiveStatus processBus(Bus& bus) { return processBus(bus, m_context); }
    /**
     * @brief Processes a bus and fills a byte collector with the received packet.
        * @tparam Bus Concrete bus type.
        * @param bus Bus instance to process.
        * @param context Context to use for processing.
        * @return Processing status.
     */
    template <class Bus>
    inline static ReceiveStatus processBus(Bus& bus, shs::DTPbusReceiveContext& context);

    /**
     * @brief Sends the current buffered packet to the handler.
        * @param handler API handler for packet processing.
        * @return Updated bus status.
     */
    inline ReceiveStatus processPacket(shs::API& handler) { sendPacket(processPacket(handler, m_context)); return m_context.status; }
    /**
     * @brief Sends the current buffered packet to the handler.
        * @param context Context containing the buffer and handler.
        * @return Updated bus status.
     */
    inline static shs::DTPpacket processPacket(shs::API& handler, shs::DTPbusReceiveContext& context);

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
protected:
    shs::DTPbusPolicy m_policy;
    shs::DTPbusReceiveContext m_context;
    shs::ProgramTime m_last_send_time;

    template <class Bus>
    static inline shs::DTPpacket m_DTPhandler(Bus& bus, shs::ByteCollectorReadIterator<> it);
};


template<class Bus>
shs::DTPbus::ReceiveStatus shs::DTPbus::checkBus(Bus& bus, shs::DTPbusReceiveContext& context)
{
    processBus(bus, context);

    if (context.handler) processPacket(*context.handler, context);

    return context.status;
}


template <class Bus>
shs::DTPbus::ReceiveStatus shs::DTPbus::processBus(Bus& bus, shs::DTPbusReceiveContext& context)
{
    if (bus.available() == 0)
    {
        context.status = ReceiveStatus::no_data;
        return context.status;
    }

    if (context.receive_length == 0)
    {
        context.receive_length = bus.read();
        context.receive_timer.reset();

        if (context.receive_length < 2)
        {
            context.status = ReceiveStatus::invalid_recipient;
            return context.status;
        }
    }
    if (context.receive_timer.expired())
    {
        context.receive_length = 0;
        while (bus.available()) bus.read();  // clear bus
        context.status = ReceiveStatus::receive_timeout_error;
        return context.status;
    }
    if (bus.available() < context.receive_length - 1)
    {
        context.status = ReceiveStatus::packet_is_expected;
        return context.status;
    }

    context.buffer.reset();
    context.buffer.push_back(context.receive_length, 1);

    for (uint8_t i = 0; i < context.receive_length - 1; i++) context.buffer.push_back(bus.read(), 1);
    context.receive_length = 0;

    context.receive_timer.reset();    // start counting time since last receive

    auto packet = m_DTPhandler(bus, context.buffer.getReadIt());
    if (!packet.empty()) sendPacket(bus, packet);

    context.status = ReceiveStatus::packet_received;
    return context.status;
}


shs::DTPpacket shs::DTPbus::processPacket(shs::API& handler, shs::DTPbusReceiveContext& context)
{
    if (context.status != ReceiveStatus::packet_received && context.status != ReceiveStatus::packet_processed) return shs::DTPpacket();

    auto it = context.buffer.getReadIt();

    context.status = ReceiveStatus::packet_processed;
    return handler.handle(it);
}

template<class Bus>
shs::DTPpacket shs::DTPbus::m_DTPhandler(Bus& bus, shs::ByteCollectorReadIterator<> it)
{
    return shs::DTP_API::static_handle(it);
}
