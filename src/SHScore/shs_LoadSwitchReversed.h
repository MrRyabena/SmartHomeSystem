#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
    v2.3.0 — used shs_pin_t for pin definitions, updated docs.
*/


#include "shs_settings_private.h"
#include "shs_Load.h"
#include "shs_LoadSwitch.h"
#include "shs_types.h"


#ifdef SHS_SF_ARDUINO

#include <GyverIO.h>


namespace shs
{
    class LoadSwitchReversed;
}


/**
 * @brief SWITCH-mode load implementation with inverted on/off logic.
 */
class shs::LoadSwitchReversed : public shs::LoadSwitch
{
public:
    /**
     * @brief Creates a switch-mode load with inverted logic on the given pin.
     */
    explicit LoadSwitchReversed(const shs::t::shs_pin_t pin, const Load::Type type = Load::Type::SWITCH_REVERSED)
        : LoadSwitch(pin, type), m_pin(pin)
    {}

    /**
     * @brief Releases the reversed switch-mode load.
     */
    ~LoadSwitchReversed() override = default;

    /**
     * @brief Inverts the requested state and delegates to the base switch logic.
     */
    void on(const uint16_t value = UINT16_MAX) override { value == 0 ? LoadSwitch::on() : LoadSwitch::off(); }

    /**
     * @brief Turns the load off by enabling the underlying switch output.
     */
    void off() override { LoadSwitch::on(); }

protected:
    const shs::t::shs_pin_t m_pin;
};

#endif  // #ifdef SHS_SF_ARDUINO
