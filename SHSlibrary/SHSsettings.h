#pragma once


// WiFi
#ifndef __AVR__
//const char* WIFI_SSID = "SHS_WiFi";
#define WIFI_SSID "SHS_WiFi"
//const char* WIFI_PASSWORD = "19711970";
#define WIFI_PASSWORD "19711970"
#endif


// debug
#ifdef DEBUG

#define dprint(val) Serial.print(val);
#define dprintln(val) Serial.println(val);
#define dprintlln(val) Serial.println(val); Serial.println();
#define dout(val1, val2) Serial.print(val1); Serial.print(F("  ")); Serial.println(val2);

#else

#define dprint(val)
#define dprintln(val)
#define dprintlln(val)
#define dout(val1, val2)

#endif