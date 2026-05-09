#include "shs_SensorAnalog.h"

#include "shs_settings_private.h"

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#endif 


shs::SensorAnalog::SensorAnalog(const shs::t::shs_pin_t pin, const uint8_t samples, const Type type)
    : Sensor(type), m_pin(pin), m_samples(samples)
{}



void shs::SensorAnalog::setup()
{
#ifdef SHS_SF_ARDUINO
    pinMode(m_pin, INPUT);
#endif
}


void shs::SensorAnalog::update()
{
#ifdef SHS_SF_ARDUINO
    uint32_t average{};
    for (auto i = 0u; i < m_samples; i++) average += analogRead(m_pin);
    m_value = static_cast<shs::t::shs_float_t>(average) / m_samples;
#endif
}


void shs::SensorAnalog::updateFast()
{
#ifdef SHS_SF_ARDUINO
    m_value = analogRead(m_pin);
#endif
}
