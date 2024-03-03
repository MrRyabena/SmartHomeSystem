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

#include <stdint.h>

namespace shs
{
    namespace Mode
    {
        enum Mode : uint8_t;
    };
    struct Config;
};

struct shs::Config
{
    uint8_t ID{};
    uint8_t serverID{};
    shs::Mode mode{};
};

enum shs::Mode::Mode : uint8_t
{
    off,
    on,
    standby,
    sleep,
};
