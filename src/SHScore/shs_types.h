#pragma once

/*
  Last update: v2.0.0
  Versions:
    v1.2.0 — created.
    v2.0.0 — developed from shs_settings_private.h.
*/

#include "SHSsettings_private.h"
#include "SHSID.h"

#include <stdint.h>

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#else
#include <string>
#endif

namespace shs
{
    namespace t
    {
#ifndef USE_FLOAT_FOR_DOUBLE
        using shs_double_t = double;
#else
        using shs_double_t = float;
#endif

#ifdef SHS_SF_ARDUINO
        using shs_string_t = String;
#else
        using shs_string_t = std::string;
#endif

        using shs_float_t = float;
        using shs_ID_t = shs::ID;
    }
}
