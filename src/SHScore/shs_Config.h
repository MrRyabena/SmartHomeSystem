#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  A structure for storing module parameters.
*/


#include "shs_types.h"

#include <stdint.h>

namespace shs
{
    enum class SystemMode : uint8_t;
    struct Config;
};

struct shs::Config
{
    //static constexpr shs::t::shs_ID_t moduleID = SHS_CONFIG_moduleID;
    shs::SystemMode mode{};
};

enum class shs::SystemMode : uint8_t
{
    off,
    on,
    standby,
    sleep,
};
