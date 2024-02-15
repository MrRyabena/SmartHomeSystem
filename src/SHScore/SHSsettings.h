#ifndef SHS_SETTINGS
#define SHS_SETTINGS

namespace shs::settings
{
// WiFi
#ifndef __AVR__
#define WIFI_SSID "SHS_WiFi"
#define WIFI_PASSWORD "19711970"
#define UPBOT_TOKEN "6956102480:AAGIKbBz_C_Z4Iluz6fZgo2LAfCGVoTYGQg"
#define TCP_PORT 50000
#define MACconstant F("SHSma")
#endif

// debug
#ifdef DEBUG

#define dprint(val) Serial.print(val);
#define dprintln(val) Serial.println(val);
#define dprintlln(val)   \
    Serial.println(val); \
    Serial.println();
#define dout(val1, val2)   \
    Serial.print(val1);    \
    Serial.print(F("  ")); \
    Serial.println(val2);

#else

#define dprint(val)
#define dprintln(val)
#define dprintlln(val)
#define dout(val1, val2)

#endif
};

#endif