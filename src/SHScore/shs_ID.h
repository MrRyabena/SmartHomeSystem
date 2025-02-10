#pragma once

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
    v2.0.0 — added comparison operators.
*/

#include <stdint.h>
#include <memory>
#include "shs_APIids.h"


namespace shs
{
    struct ID;
};


struct shs::ID
{
    uint32_t id{};

    using ID_t = uint32_t;
    using moduleID_t = uint8_t;
    using deviceID_t = uint8_t;
    using componentID_t = uint16_t;

    constexpr ID(const moduleID_t module_id = 0, const deviceID_t device_id = 0, const componentID_t component_id = 0)
        : id(((uint32_t)module_id << 24) | ((uint32_t)device_id << 16) | (component_id & 0xffff))
    {}

    constexpr ID(const ID& other) : id(other.id) {}
    constexpr ID& operator=(const ID& other) { id = other.id; return *this; }

    ~ID() = default;

    constexpr moduleID_t getModuleID() const { return id >> 24; }
    constexpr deviceID_t getDeviceID() const { return (id >> 16) & 0xff; }
    constexpr componentID_t getComponentID() const { return id & 0xffff; }

    shs::ID& setModuleID(const moduleID_t module)
    {
        id |= (uint32_t)module << 24;
        return *this;
    }

    shs::ID& setDeviceID(const deviceID_t device)
    {
        id |= (uint32_t)device << 16;
        return *this;
    }

    shs::ID& setComponentID(const componentID_t api)
    {
        id |= api & 0xffff;
        return *this;
    }

    shs::ID& setComponentID(const shs::constants::APIids api) { return setComponentID(static_cast<componentID_t>(api)); }


    bool operator<(const shs::ID& other) const { return id < other.id; }
    bool operator>(const shs::ID& other) const { return id > other.id; }
    bool operator==(const shs::ID& other) const { return id == other.id; }
    bool operator!=(const shs::ID& other) const { return id != other.id; }
};
