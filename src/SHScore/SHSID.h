#pragma once

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
    v2.0.0 — added comparison operators.
*/

#include <stdint.h>

namespace shs
{
    struct ID;
};

struct shs::ID
{
    uint32_t id{};

    ID(const uint8_t module = 0, const uint8_t device = 0, const int16_t api = 0)
        : id(((uint32_t)module << 24) | ((uint32_t)device << 16) | (api & 0xffff)) {}

    ~ID() = default;

    uint8_t getModuleID() const { return id >> 24; }
    uint8_t getDeviceID() const { return (id >> 16) & 0xff; }
    int16_t getAPI() const { return id & 0xffff; }

    shs::ID &setModuleID(const uint8_t module)
    {
        id |= (uint32_t)module << 24;
        return *this;
    }

    shs::ID &setDeviceID(const uint8_t device)
    {
        id |= (uint32_t)device << 16;
        return *this;
    }

    shs::ID &setAPI(const int16_t api)
    {
        id |= api & 0xffff;
        return *this;
    }

    bool operator<(const shs::ID &other) const { return id < other.id; }
    bool operator>(const shs::ID &other) const { return id > other.id; }
    bool operator==(const shs::ID &other) const { return id == other.id; }
    bool operator!=(const shs::ID &other) const { return id != other.id; }
};
