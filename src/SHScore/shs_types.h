#pragma once

/*
  Last update: v2.0.0
  Versions:
    v1.2.0 — created.
    v2.0.0 — developed from shs_settings_private.h.
*/

#include "shs_settings_private.h"
#include "shs_ID.h"

#include <stdint.h>


#ifdef SHS_SF_ARDUINO
#include <Arduino.h>

#ifdef SHS_SF_ESP8266

#include <WiFiUdp.h>

#elif defined(SHS_SF_ESP32)
#include <WiFiUdp.h>
#elif defined(SHS_SF_AVR)
#endif

#else
#include <string>
#endif


namespace shs
{
    namespace t
    {
    #ifndef USE_FLOAT_FOR_DOUBLE
        using shs_double_t = double;
    #else
        using shs_double_t = float;
    #endif

    #ifdef SHS_SF_ARDUINO
        using shs_string_t = String;

        using shs_IP_t = IPAddress;
    #else
        using shs_string_t = std::string;

        using shs_IP_t = uint32_t;
    #endif

        using shs_float_t = float;
        using shs_ID_t = shs::ID;
        using shs_busID_t = uint16_t;

        using shs_port_t = uint16_t;
    }
}
