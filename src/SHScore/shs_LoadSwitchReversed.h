#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/


#include "shs_settings_private.h"
#include "shs_Load.h"
#include "shs_LoadSwitch.h"


#ifdef SHS_SF_ARDUINO

#include <GyverIO.h>


namespace shs
{
    class LoadSwitchReversed;
}


/*
  A class for reversed controlling the load in SWITCH mode.
*/
class shs::LoadSwitchReversed : public shs::LoadSwitch
{
public:
    explicit LoadSwitchReversed(const uint8_t pin, const Load::Type type = Load::Type::SWITCH_REVERSED)
        : LoadSwitch(pin, type), m_pin(pin)
    {}

    ~LoadSwitchReversed() override = default;

    void on(const uint16_t value = UINT16_MAX) override { LoadSwitch::off(); }
    void off() override { LoadSwitch::on(); }

protected:
    const uint8_t m_pin;
};

#endif  // #ifdef SHS_SF_ARDUINO
