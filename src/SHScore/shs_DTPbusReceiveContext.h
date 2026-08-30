#pragma once

#include <memory>

#include <stdint.h>

#include "shs_API.h"
#include "shs_ByteCollector.h"
#include "shs_ProgramTimer.h"

namespace shs
{
    struct DTPbusReceiveContext;
}

/**
 * @brief A context for managing the reception of DTP packets.
 */
struct shs::DTPbusReceiveContext
{
    /**
    * @brief The size type for DTP bus operations.
    */
    using DtpBusSize_t = uint8_t;

    static constexpr auto RECEIVE_TIMEOUT = 10'000;  // ms
    static constexpr auto DEFAULT_BUFFER_SIZE = 32;  // bytes


    DTPbusReceiveContext() = default;
    explicit DTPbusReceiveContext(const DtpBusSize_t bufsize, shs::API* handler = nullptr,
        shs::t::shs_time_t receive_timeout = RECEIVE_TIMEOUT);
    explicit DTPbusReceiveContext(const DTPbusReceiveContext&) = default;
    explicit DTPbusReceiveContext(DTPbusReceiveContext&& other) noexcept;
    DTPbusReceiveContext& operator=(const DTPbusReceiveContext&) = default;
    DTPbusReceiveContext& operator=(DTPbusReceiveContext&& other) noexcept;


    /**
     * @brief The buffer for storing incoming data.
     */
    shs::ByteCollector<> buffer{ DEFAULT_BUFFER_SIZE };
    /**
     * @brief The length of the receiving packet.
     */
    DtpBusSize_t receive_length{};
    /**
     * @brief Timer for tracking receive time.
     */
    shs::ProgramTimer receive_timer{ RECEIVE_TIMEOUT };
    /**
     * @brief The API handler for processing incoming packets.
     */
    shs::API* handler{};
};
