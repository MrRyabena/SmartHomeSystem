#pragma once

/*
  Last update: v2.1.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
      - Added inline.
      - Corrected.
    v2.1.0 — returned to development, redesigned, debugged and tested.
    v2.3.0 — used shs_pin_t for pin definitions, updated docs.
*/

#include "shs_settings_private.h"
#include "shs_Load.h"
#include "shs_types.h"


#ifdef SHS_SF_ARDUINO

#include <Arduino.h>


namespace shs
{
    class LoadPWM;
}


/**
 * @brief Load implementation that drives a PWM output.
 */
class shs::LoadPWM : public shs::Load
{
public:
    /**
     * @brief Creates a PWM load bound to an output pin.
     */
    explicit LoadPWM(const shs::t::shs_pin_t pin, const Load::Type type = Load::Type::PWM)
        : Load(type), m_pin(pin)
    {}

    /**
     * @brief Releases the PWM load.
     */
    ~LoadPWM() override = default;

    /**
     * @brief Configures the PWM pin for output.
     */
    void setup() override
    {
   // #ifdef SHS_SF_ESP32
        
   // #else
        pinMode(m_pin, OUTPUT);
   // #endif
    }

    /**
     * @brief Sets the PWM duty cycle and stores the applied value.
     */
    void on(const uint16_t value = UINT16_MAX) override { analogWrite(m_pin, value); m_value = value; }

    /**
     * @brief Disables PWM output.
     */
    void off() override { analogWrite(m_pin, 0); m_value = 0; }

protected:
    const shs::t::shs_pin_t m_pin;
};

#endif  // #ifdef SHS_SF_ARDUINO
