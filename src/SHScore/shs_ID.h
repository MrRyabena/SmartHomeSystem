#pragma once

/*
  Last update: v2.1.0
  Versions:
    v1.2.0 — created.
    v2.0.0 — added comparison operators.
    v2.1.0 — fixed a bug during the assignment of ID components.
*/

#include "shs_settings_private.h"

#include <stdint.h>

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#else
#include <string>
#endif

#include "shs_APIids.h"
#include "shs_debug.h"

namespace shs
{
    struct ID;
};


/**
 * @brief Packed identifier that stores module, device, and component IDs in one value.
 */
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
    ID& operator=(const ID& other) { id = other.id; return *this; }

    ~ID() = default;

    constexpr moduleID_t getModuleID() const { return id >> 24; }
    constexpr deviceID_t getDeviceID() const { return (id >> 16) & 0xff; }
    constexpr componentID_t getComponentID() const { return id & 0xffff; }

    shs::ID& setModuleID(const moduleID_t module)
    {
        id = (id & 0x00FFFFFFu) | ((uint32_t)module << 24);
        return *this;
    }

    shs::ID& setDeviceID(const deviceID_t device)
    {
        id = (id & 0xFF00FFFFu) | ((uint32_t)device << 16);
        return *this;
    }

    shs::ID& setComponentID(const componentID_t api)
    {
        id = (id & 0xFFFF0000u) | (api & 0xffffu);
        return *this;
    }

    shs::ID& setComponentID(const shs::constants::APIids api) { return setComponentID(static_cast<componentID_t>(api)); }

    ID_t operator&(const shs::ID& other) const { return id & other.id; }

    bool operator<(const shs::ID& other) const { return id < other.id; }
    bool operator>(const shs::ID& other) const { return id > other.id; }
    bool operator==(const shs::ID& other) const { return id == other.id; }
    bool operator!=(const shs::ID& other) const { return id != other.id; }

private:
#ifdef SHS_SF_ARDUINO
    using m_string_t = String;
#else
    using m_string_t = std::string;
#endif

public:

#ifdef SHS_SF_DEBUG
    m_string_t toDebug() const
    {
    #ifdef SHS_SF_ARDUINO
        return m_string_t(static_cast<uint32_t>(getModuleID())) + ' ' +
            static_cast<uint32_t>(getDeviceID()) + ' ' +
            static_cast<uint32_t>(getComponentID());
    #else
        return std::to_string(static_cast<uint32_t>(getModuleID())) + ' ' +
            std::to_string(static_cast<uint32_t>(getDeviceID())) + ' ' +
            std::to_string(static_cast<uint32_t>(getComponentID()));
    #endif
    }
#endif
};
