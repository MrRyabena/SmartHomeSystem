#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
      - Added inline.
      - Corrected.
    v2.0.0 — redesigned, debugged and tested.
    v2.3.0 — used shs_pin_t for pin definitions, updated docs.
*/

#include "shs_settings_private.h"
#include "shs_Load.h"
#include "shs_types.h"


#ifdef SHS_SF_ARDUINO

#include <GyverIO.h>


namespace shs
{
    class LoadSwitch;
}


/**
 * @brief Load implementation that controls a digital output in SWITCH mode.
 */
class shs::LoadSwitch : public shs::Load
{
public:
    /**
     * @brief Creates a switch-mode load bound to a digital output pin.
     */
    explicit LoadSwitch(const shs::t::shs_pin_t pin, const Load::Type type = Load::Type::SWITCH)
        : Load(type), m_pin(pin)
    {}

    /**
     * @brief Releases the switch-mode load.
     */
    ~LoadSwitch() override = default;

    /**
     * @brief Configures the output pin for digital output.
     */
    void setup() override
    {
    #ifdef SHS_SF_ESP
        gio::init(m_pin, OUTPUT);
    #else
        gio::mode(m_pin, OUTPUT);
    #endif
    }

    /**
     * @brief Turns the load on by writing a logical high value.
     * @param value Switch off if 0, switch on otherwise.
     */
    void on(const uint16_t value = UINT16_MAX) override { gio::write(m_pin, value); m_value = static_cast<bool>(value); }

    /**
     * @brief Turns the load off by writing a logical low value.
     */
    void off() override { gio::low(m_pin); m_value = 0; }

protected:
    const shs::t::shs_pin_t m_pin;
};

#endif  // #ifdef SHS_SF_ARDUINO
