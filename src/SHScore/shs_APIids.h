#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/

/*
  
*/

#include <stdint.h>

namespace shs
{
    namespace constants
    {
        enum class APIids : uint16_t;
    }
}


enum class shs::constants::APIids : uint16_t
{
    NOID,

    DTP = 0x01,
    DTPbus,
    DTPserver_bus,
    DTPdiscover,

    Load,
    Sensor,
    EventTracker,


    SHS_LIBRARY_IDs = 0x4000,
    USER_IDs = 0x8000,

};
