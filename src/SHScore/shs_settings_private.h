#ifndef _shs_SETTINGS_PRIVATE_   // note: don't use <#pragma once> in settings files!
#define _shs_SETTINGS_PRIVATE_

/*
  Last update: v2.1.0
  Versions:
    v0.1.0 — created.
    v2.0.0 — added a lot of compilation flags and default constants.
    v2.1.0 — added pragma message to debug flag.
*/

#pragma message "shs_settings_private"


#include <shs_settings.h>
#define SHS_SF_SETTINGS

#ifdef USE_FLOAT_FOR_DOUBLE
#define SHS_SF_USE_FLOAT_FOR_DOUBLE
#pragma message "Used float for double."
#undef USE_FLOAT_FOR_DOUBLE
#endif

#include <stdint.h>

#define SHS_SF_NETWORK

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
#undef SHS_SF_NETWORK

#endif 

#elif defined(SHS_QT_FLAG)
#define SHS_SF_QT
#endif


#if defined(DEBUG) && !defined(SHS_SF_DEBUG)
#define SHS_SF_DEBUG
#pragma message "Defined debug!"
#endif


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

    #ifdef SHS_SET_WIFI_SSID
        constexpr auto WIFI_SSID = SHS_SET_WIFI_SSID;
    #else 
        constexpr auto WIFI_SSID = "";
    #endif

    #ifdef SHS_SET_WIFI_PASSWORD
        constexpr auto WIFI_PASSWORD = SHS_SET_WIFI_PASSWORD;
    #else
        constexpr auto WIFI_PASSWORD = "";
    #endif

    #ifndef SHS_SET_GMT
    #define SHS_SET_GMT 0
    #endif
        constexpr auto GMT = SHS_SET_GMT;


    }
}
#endif
