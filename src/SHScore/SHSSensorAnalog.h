#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — made purely virtual.
    v1.0.0 — release.
*/

/*
  A class for getting values from analog pins to which sensors are connected.
*/

#include "SHSSensor.h"
#include "SHSsettings_private.h"
#include <Arduino.h>

namespace shs
{
    class SensorAnalog;
};

class shs::SensorAnalog : public shs::Sensor
{
public:
    explicit SensorAnalog(const shs::settings::shs_ID_t ID = 0, const shs::SensorType::SensorType stype = shs::SensorType::unknown, const uint8_t pin = A0);

    void setup() override;
    shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID = 0) override;
    int16_t getValueI(const shs::settings::shs_ID_t ID = 0) override;

    shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID = 0) override;
    int16_t getAverageI(const shs::settings::shs_ID_t ID = 0) override;

protected:
    uint8_t m_pin{};
    uint16_t m_getSamplesSum(const uint8_t count = shs::settings::SENSOR_AVERAGE_SAMPLES);
};
