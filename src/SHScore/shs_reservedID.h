#pragma once

#include <stdint.h>

namespace shs
{
    enum class ApiIDreserved : uint16_t;
    enum class DeviceIDreserved : uint8_t;
}


enum class shs::ApiIDreserved : uint16_t
{
    DTP = 0x01,
};


enum class shs::DeviceIDreserved : uint8_t
{
    DTPbus = 0x01,
    DTPserver_bus = 0x02,
};
