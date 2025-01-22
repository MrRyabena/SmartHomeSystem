#ifndef _shs_SETTINGS_PRIVATE_   // note: don't use <#pragma once> in settings files!
#define _shs_SETTINGS_PRIVATE_

#include <stdint.h>

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#define SHS_SF_ARDUINO

#if defined(ESP8266)
#define SHS_SF_ESP8266
#define SHS_SF_ESP

#elif defined(ESP32)
#define SHS_SF_ESP32
#define SHS_SF_ESP

#elif defined(__AVR__)
#define SHS_SF_AVR
#define SHS_SF_UNUSE_STL
#endif 

#elif defined(SHS_QT_FLAG)
#define SHS_SF_QT
#endif


#define DEBUG

#include "shs_types.h"

namespace shs
{
    namespace settings
    {

    #ifndef SHS_SET_SENSOR_AVERAGE_SAMPLES
    #define SHS_SET_SENSOR_AVERAGE_SAMPLES 20
    #endif

    #ifndef SHS_SET_DEFAULT_TCP_PORT
    #define SHS_SET_DEFAULT_TCP_PORT 5000
    #endif
    #ifndef SHS_SET_DEFAULT_UDP_PORT
    #define SHS_SET_DEFAULT_UDP_PORT 6000
    #endif
    #ifndef SHS_SET_DEFAULT_MULTICAST_IP
    #define SHS_SET_DEFAULT_MULTICAST_IP "224.0.0.4"
    #endif
    #ifndef SHS_SET_DEFAULT_BROADCAST_IP
    #define SHS_SET_DEFAULT_BROADCAST_IP "192.168.1.255"
    #endif
        constexpr auto DEFAULT_TCP_PORT = SHS_SET_DEFAULT_TCP_PORT;
        constexpr auto DEFAULT_UDP_PORT = SHS_SET_DEFAULT_UDP_PORT;
        constexpr auto DEFAULT_MULTICAST_IP = SHS_SET_DEFAULT_MULTICAST_IP;
        constexpr auto DEFAULT_BROADCAST_IP = SHS_SET_DEFAULT_BROADCAST_IP;
    #undef SHS_SET_DEFAULT_TPC_PORT
    #undef SHS_SET_DEFAULT_UDP_PORT
    #undef SHS_SET_DEFAULT_MULTICAST_IP
    #undef SHS_SET_DEFAULT_BROADCAST_IP
    }
}
#endif
