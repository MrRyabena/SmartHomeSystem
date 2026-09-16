#pragma once

#ifdef SHS_SF_DEBUG
#ifndef SHS_SF_AVR
#include <array>
#include <ostream>
#endif
#include "shs_types.h"
#endif  // SHS_SF_DEBUG

#include <stdint.h>

#include "shs_settings_private.h"

namespace shs
{
    enum class DTPbusReceiveStatus : uint8_t
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

#ifndef SHS_SF_AVR
    /**
     * @brief An array of strings representing the names of each DTPbusStatus.
     */
    constexpr std::array<const char*, static_cast<size_t>(DTPbusReceiveStatus::count)> DTPbusReceiveStatusNames = {
            "no_data",
            "packet_is_expected",
            "packet_received",
            "packet_processed",
            "invalid_recipient",
            "bus_error",
            "receive_timeout_error"
    };

    inline std::ostream& operator<<(std::ostream& os, DTPbusReceiveStatus status)
    {
        os << "DTPbusStatus::" << DTPbusReceiveStatusNames[static_cast<size_t>(status)];
        return os;
    }
#else
    constexpr const char* DTPbusReceiveStatusNames[] = {
                "no_data",
                "packet_is_expected",
                "packet_received",
                "packet_processed",
                "invalid_recipient",
                "bus_error",
                "receive_timeout_error"
    };
#endif  // #ifndef SHS_SF_AVR

    inline shs::t::shs_string_t to_string(DTPbusReceiveStatus status)
    {
        return DTPbusReceiveStatusNames[static_cast<size_t>(status)];
    }

#endif  // SHS_SF_DEBUG

}  // namespace shs
