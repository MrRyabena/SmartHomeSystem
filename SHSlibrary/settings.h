#pragma once


// WiFi
#define WIFI_SSID "lady"
#define WIFI_PASSWORD "19711970"



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