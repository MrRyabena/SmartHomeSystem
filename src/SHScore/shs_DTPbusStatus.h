#pragma once

#ifdef SHS_SF_DEBUG
#include <array>
#include <ostream>
#endif  // SHS_SF_DEBUG

#include <stdint.h>

#include "shs_settings_private.h"

namespace shs
{
    enum class DTPbusStatus : uint8_t
    {
        no_data,
        packet_is_expected,
        packet_received,
        packet_processed,
        invalid_recipient,
        bus_error,
        receive_timeout_error,

        count
    };

#ifdef SHS_SF_DEBUG

    /**
     * @brief An array of strings representing the names of each DTPbusStatus.
     */
    constexpr std::array<const char*, static_cast<size_t>(DTPbusStatus::count)> DTPbusStatusNames = {
            "no_data",
            "packet_is_expected",
            "packet_received",
            "packet_processed",
            "invalid_recipient",
            "bus_error",
            "receive_timeout_error"
    };

    std::ostream& operator<<(std::ostream& os, DTPbusStatus status)
    {
        os << "DTPbusStatus::" << DTPbusStatusNames[static_cast<size_t>(status)];
        return os;
    }

#endif  // SHS_SF_DEBUG

}  // namespace shs
