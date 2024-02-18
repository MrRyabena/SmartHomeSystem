#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>

namespace shs
{
    struct Config;
    enum Mode;
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
    standby,
    sleep,
};