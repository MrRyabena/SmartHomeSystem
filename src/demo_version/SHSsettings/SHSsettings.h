#pragma once
#ifndef SHS_SETTINGS // note: don't use <#pragma once> in settings files!
#define SHS_SETTINGS

#include <stdint.h>

#define _Arduino_

namespace shs::settings
{
// WiFi
/* #ifndef __AVR__
#define connectWiFi_NORESTART
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
#define UPBOT_TOKEN F("")
inline const uint16_t TCP_PORT = 50000;
uint8_t COM_IP[] = { 192, 168, 1, 0 };
const uint8_t MACconstant[6] = {0x53, 0x48, 0x53, 0x6D, 0x61, 0x00};
#endif
 */
//#define USE_FLOAT_FOR_DOUBLE


inline const uint8_t ServerID = 4;
inline const uint8_t SmartThermID = 5;
inline const uint8_t SmartFanID = 6;
inline const uint8_t SmartLighterID = 7;
inline const uint8_t appID = 10;

inline const int8_t ledBulbID = -11;
inline const int8_t photoID = -12;
inline const int8_t thermID = -13;
inline const int8_t bulbID = -14;


// #define DEBUG

};

#endif
