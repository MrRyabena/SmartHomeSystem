#pragma once

/*
  Last update: v2.1.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
      - Added inline.
      - Corrected.
    v2.1.0 — returned to development, redesigned, debugged and tested.
*/

#include "shs_settings_private.h"
#include "shs_Load.h"


#ifdef SHS_SF_ARDUINO

#include <Arduino.h>


namespace shs
{
    class LoadPWM;
}


/*
  A class for controlling the load in PWM mode.
*/
class shs::LoadPWM : public shs::Load
{
public:
    explicit LoadPWM(const uint8_t pin, const Load::Type type = Load::Type::PWM)
        : Load(type), m_pin(pin)
    {}

    ~LoadPWM() override = default;

    void setup() override
    {
   // #ifdef SHS_SF_ESP32
        
   // #else
        pinMode(m_pin, OUTPUT);
   // #endif
    }

    void on(const uint16_t value = UINT16_MAX) override { analogWrite(m_pin, value); m_value = value; }
    void off() override { analogWrite(m_pin, 0); m_value = 0; }

protected:
    const uint8_t m_pin;
};

#endif  // #ifdef SHS_SF_ARDUINO
