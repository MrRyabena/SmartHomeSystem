#pragma once

/*
    Last update: v1.0.0
    Versions:
        v0.1.0 — created.
        v0.2.0 — corrected.
        v1.0.0 — release.
            - Namespaces added.
            - Variable names have been corrected.
*/

/*
    An abstract class describing a load (electrical device or component).
*/

#include <stdint.h>

#include "shs_settings_private.h"
#include "shs_types.h"


namespace shs
{
    class Load;
}


class shs::Load
{
public:

    enum Type : uint8_t
    {
        UNKNOWN,
        SWITCH,
        PID,
        PWM,
        DIMMER,
        USER_TYPES,
    }
    const type
        ;


    explicit Load(const Type l_type = UNKNOWN) : type(l_type) {}

    virtual ~Load() = default;


    virtual void setup() = 0;

    virtual void on(const uint16_t value = UINT16_MAX) = 0;

    virtual void off() = 0;

    [[nodiscard]] uint16_t getValue() const noexcept { return m_value; }

protected:
    uint16_t m_value;

};
