
#ifndef _SHSSettings_private_ // note: don't use <#pragma once> in settings files!
#define _SHSSettings_private_

#include <stdint.h>

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#define SHS_SF_ARDUINO

#if defined(ESP8266)
#define SHS_SF_ESP8266

#elif defined(ESP32)
#define SHS_SF_ESP32

#elif defined(_AVR_)
#define SHS_SF_AVR
#endif

#endif

#define DEBUG

namespace shs
{
        namespace settings
        {
                const uint8_t SENSOR_AVERAGE_SAMPLES = 20;
                // const uint8_t COM_IP[] = {192, 168, 1, 4};
                const uint8_t SERVER_ID = 4;

                const int8_t Load_apiID = -1;
                const int8_t Sensor_apiID = -2;
        }
}
#endif
