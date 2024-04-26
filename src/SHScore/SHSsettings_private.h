
#ifndef _SHSSettings_private_ // note: don't use <#pragma once> in settings files!
#define _SHSSettings_private_

#include <stdint.h>

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#define ARDUINO
#else
#include <string>
#endif

#define DEBUG

namespace shs
{
        namespace settings
        {
#ifndef USE_FLOAT_FOR_DOUBLE
                using shs_double_t = double;
#else
                using shs_double_t = float;
#endif

#ifdef ARDUINO
                using shs_string_t = String;
#else
                using shs_string_t = std::string;
#endif

                using shs_float_t = float;
                using shs_ModuleID_t = uint8_t;
                using shs_ID_t = int16_t;

                const uint8_t SENSOR_AVERAGE_SAMPLES = 20;
                // const uint8_t COM_IP[] = {192, 168, 1, 4};
                const uint8_t SERVER_ID = 4;

                const int8_t Load_apiID = -1;
                const int8_t Sensor_apiID = -2;

        }
}
#endif
