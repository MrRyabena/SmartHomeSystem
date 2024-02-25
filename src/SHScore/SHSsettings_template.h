#ifndef SHS_SETTINGS // note: don't use <#pragma once> in settings files!
#define SHS_SETTINGS

namespace shs::settings
{
// WiFi
#ifndef __AVR__
#define WIFI_SSID F("")
#define WIFI_PASSWORD F("")
#define UPBOT_TOKEN F("")
#define TCP_PORT 50000
#define MACconstant F("SHSma")
#endif

//#define USE_FLOAT_FOR_DOUBLE

// #define DEBUG

};

#endif