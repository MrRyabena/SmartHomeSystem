#pragma once

#include <stdint.h>

namespace shs
{
    enum class DTPbusPolicy : uint8_t
    {
        UNKNOWN_POLICY,

        /// @brief Bus is considered static and will not be checked for connection issues.
        STATIC_BUS,

        /// @brief Bus can be removed if no packets are received within the timeout. 
        TEMPORARY_IF_NO_ANSWERS,

        /// @brief Bus can be removed if it is disconnected or no packets are received within the timeout.
        TEMPORARY_IF_DISCONNECTED,

        /// @brief Bus can be removed if it is not used (DTP_API packets are not counted) within the timeout.
        TEMPORARY_IF_UNUSED,
    };
}
