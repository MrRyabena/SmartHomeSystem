
#ifndef _SHSSettings_private_ // note: don't use <#pragma once> in settings files!
#define _SHSSettings_private_

#include <stdint.h>

namespace shs::settings
{
    using shs_double_t = double;
    using shs_float_t = float;
    using shs_ModuleID_t = uint8_t;
    using shs_ID_t = int16_t;

#define SENSOR_AVERAGE_SAMPLES 20
};

#endif
