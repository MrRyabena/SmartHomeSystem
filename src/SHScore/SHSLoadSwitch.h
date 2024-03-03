#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
      - Added inline.
      - Corrected.
*/

/*
  A class for controlling the load in SWITCH mode.
*/

#include "SHSLoad.h"
#include "SHSProcess.h"
#include "SHSProcessesKeeper.h"
#include <Arduino.h>

namespace shs
{
    class LoadSwitch;
};

class shs::LoadSwitch : public shs::Load, protected shs::Process
{
public:
    explicit LoadSwitch(shs::settings::shs_ID_t ID = 0, uint8_t pin = 0,
                        shs::LoadType::LoadType ltype = shs::LoadType::SWITCH);

    void setup() override;

    void on(const uint8_t value = 255, const uint8_t smoother = 0, const shs::settings::shs_ID_t ID = 0) override;
    void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void begin() override;
    void tick() override;
    void end() override;

protected:
    uint8_t m_pin{};
};