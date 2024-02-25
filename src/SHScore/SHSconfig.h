#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>

namespace shs
{
    enum Mode : uint8_t;
    struct Config;
};

struct shs::Config
{
    uint8_t ID{};
    uint8_t serverID{};
    shs::Mode mode{};
};

enum shs::Mode : uint8_t
{
    off,
    on,
    standby,
    sleep,
};