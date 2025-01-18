#pragma once

#include "shs_settings_private.h"

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
    explicit SensorAnalog(const uint8_t pin) : Sensor(shs::Sensor::Type::ANALOG_PIN), m_pin(pin) {}

    static constexpr uint8_t SENSOR_AVERAGE_SAMPLES = SHS_SET_SENSOR_AVERAGE_SAMPLES;

    void setup() override { pinMode(m_pin, INPUT); }

    void update() override
    {
        uint32_t average{};
        for (uint8_t i = 0; i < SENSOR_AVERAGE_SAMPLES; i++) average += analogRead(m_pin);
        m_value = shs::t::shs_float_t(average) / SENSOR_AVERAGE_SAMPLES;
    }

    void updateFast() override { m_value = analogRead(m_pin); }
    [[nodiscard]] bool isUpdated() override { return true; }


    [[nodiscard]] int32_t              getValueI() override { return m_value; }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx() override { return m_value; }
    [[nodiscard]] shs::t::shs_float_t  getValueF() override { return static_cast<shs::t::shs_float_t>(m_value); }
    [[nodiscard]] shs::t::shs_double_t getValueD() override { return static_cast<shs::t::shs_double_t>(m_value); }

private:
    shs::t::shs_fixed_t m_value;
    const uint8_t m_pin;
};
