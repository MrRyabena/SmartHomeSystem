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
#include "SHSsettings_private.h"
#include "SHSProcess.h"
#include "SHSProcessesKeeper.h"

namespace shs
{
    namespace LoadType
    {
        enum LoadType : uint8_t;
    };

    class Load;
};

enum shs::LoadType::LoadType : uint8_t
{
    UNKNOWN,
    SWITCH,
    PID,
    PWM,
    DIMMER,
};

class shs::Load
{
public:
    shs::LoadType::LoadType type;

public:
    explicit Load(shs::settings::shs_ID_t ID = 0, shs::LoadType::LoadType ltype = shs::LoadType::UNKNOWN);

    void setID(const shs::settings::shs_ID_t ID);
    shs::settings::shs_ID_t getID() const;

    virtual void setup() = 0;

    virtual void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;
    virtual void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;

    virtual void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;

protected:
    shs::settings::shs_ID_t m_loadID{};
};
