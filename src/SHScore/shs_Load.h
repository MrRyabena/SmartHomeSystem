#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — corrected.
    v1.0.0 — release.
      - Namespaces added.
      - Variable names have been corrected.
    v2.0.0 — redesigned, debugged and tested.
    v2.3.0 — updated docs.
*/


#include <stdint.h>

#include "shs_settings_private.h"
#include "shs_types.h"


namespace shs
{
    class Load;
}


/**
 * @brief Abstract load interface for controllable electrical devices and components.
 */
class shs::Load
{
public:

    /**
     * @brief Describes supported load types.
     */
    enum Type : uint8_t
    {
        UNKNOWN,
        SWITCH,
        SWITCH_REVERSED,
        PID,
        PWM,
        DIMMER,
        USER_TYPES,
    }
    const type
        ;


    /**
     * @brief Creates a load with the specified type.
     */
    explicit Load(const Type l_type = UNKNOWN) : type(l_type) {}

    /**
     * @brief Releases the load interface.
     */
    virtual ~Load() = default;


    /**
     * @brief Performs hardware initialization for the load.
     */
    virtual void setup() = 0;

    /**
     * @brief Turns the load on and optionally applies a value.
     */
    virtual void on(const uint16_t value = UINT16_MAX) = 0;

    /**
     * @brief Turns the load off.
     */
    virtual void off() = 0;

    /**
     * @brief Returns the current load value.
     */
    [[nodiscard]] uint16_t getValue() const noexcept { return m_value; }

protected:
    /**
     * @brief Stored load value.
     */
    uint16_t m_value;

};
