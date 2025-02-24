#pragma once

#include "shs_settings_private.h"

#ifdef SHS_SF_ARDUINO


#include <Arduino.h>

#include "shs_Sensor.h"
#include "shs_types.h"


namespace shs
{
    class SensorAnalog;
}


class shs::SensorAnalog : public shs::Sensor
{
public:
    explicit SensorAnalog(const uint8_t pin, const uint8_t samples = SENSOR_AVERAGE_SAMPLES)
        : Sensor(shs::Sensor::Type::ANALOG_PIN), m_pin(pin), m_samples(samples)
    {}

    static constexpr uint8_t SENSOR_AVERAGE_SAMPLES = SHS_SET_SENSOR_AVERAGE_SAMPLES;

    void setSamples(const uint8_t samples) { m_samples = samples; }
    uint8_t getSamples() const { return m_samples; }

    void setup() override { pinMode(m_pin, INPUT); }

    void update() override
    {
        uint32_t average{};
        for (auto i = 0u; i < m_samples; i++) average += analogRead(m_pin);
        m_value = shs::t::shs_float_t(average) / m_samples;
    }

    void updateFast() override { m_value = analogRead(m_pin); }
    [[nodiscard]] bool isUpdated() override { return true; }
    [[nodiscard]] uint8_t getStatus() override { return 0; }


    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return m_value; }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return m_value; }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override { return static_cast<shs::t::shs_float_t>(m_value); }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(m_value); }

protected:
    shs::t::shs_fixed_t m_value;
    const uint8_t m_pin;
    uint8_t m_samples;
};


#endif  // #ifdef SHS_SF_ARDUINO
