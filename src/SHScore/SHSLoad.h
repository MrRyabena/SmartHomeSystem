#pragma once

#include <stdint.h>
#include "SHSsettings_private.h"
#include "SHSProcess.h"
#include "SHSProcessesKeeper.h"

namespace shs
{
    enum LoadType : uint8_t;
    class Load;
};

enum shs::LoadType : uint8_t
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
    shs::LoadType type;

public:
    explicit Load(shs::settings::shs_ID_t ID = 0, shs::LoadType ltype = shs::LoadType::UNKNOWN);

    void setID(const shs::settings::shs_ID_t ID);
    shs::settings::shs_ID_t getID() const;

    virtual void setup() = 0;

    virtual void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;
    virtual void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;

    virtual void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;

protected:
    shs::settings::shs_ID_t m_ID{};
};
