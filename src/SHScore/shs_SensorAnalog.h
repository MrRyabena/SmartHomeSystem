#pragma once

/*
  Last update: v2.1.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — made purely virtual.
    v1.0.0 — release.
    v2.0.0 — redesigned, debugged and tested.
      - The functionality has been changed
      - update() must be called before getting the value.
      - updateFast(), if supported by the sensor, measures less accurately, but faster.
      - Added error status.
      - Support for multiple metrics.
    v2.1.0 — updated according to the changes in the base class.
    v2.2.0 — fixed a bug in function getCacheExpiration().
    v2.3.0 — 
      - Separated into .h and .cpp files.
      - Value type of protected member m_value replaced from shs::t::shs_fixed_t 
        to shs::t::shs_float_t.
      - The class is available for compilation without the flag SHS_SF_ARDUINO, but the functions 
        are presented as stubs, without implementing the functionality.
      - Value type of protected member m_pin replaced from uint8_t to shs::t::shs_pin_t.
*/


#include "shs_types.h"


namespace shs
{
    class Sensor;          // declared in shs_Sensor.h
    class SensorAnalog;
}


/**
 * @brief
 * A class for getting values from analog pins to which sensors are connected.
 * 
 * @note The class is available for compilation without the flag SHS_SF_ARDUINO, but the functions 
 *       are presented as stubs, without implementing the functionality.
*/
class shs::SensorAnalog : public shs::Sensor
{
public:
    explicit SensorAnalog(const uint8_t pin, const uint8_t samples = SENSOR_AVERAGE_SAMPLES)
        : Sensor(shs::Sensor::Type::ANALOG_PIN), m_pin(pin), m_samples(samples)
    {}

    static constexpr uint8_t SENSOR_AVERAGE_SAMPLES = SHS_SET_SENSOR_AVERAGE_SAMPLES;

    void setSamples(const uint8_t samples) { m_samples = samples; }
    [[nodiscard]] uint8_t getSamples() const { return m_samples; }

    void setup() override;

    void update() override;
    void updateFast() override;
    void updateForced(bool fast = false) override { fast ? updateFast() : update(); }
    [[nodiscard]] bool isUpdated() override { return true; }
    [[nodiscard]] uint8_t getStatus() override { return 0; }

    void clearCache() override {}
    void setCacheExpiration(const uint32_t expiration_time) override {}
    [[nodiscard]] uint32_t getCacheExpiration() const override { return 0; }

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return static_cast<int32_t>(m_value); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return static_cast<shs::t::shs_fixed_t>(m_value); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override { return m_value; }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(m_value); }

protected:
    shs::t::shs_float_t m_value;
    const shs::t::shs_pin_t m_pin;
    uint8_t m_samples;
};
