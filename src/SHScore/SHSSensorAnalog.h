#pragma once

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
    explicit SensorAnalog(const shs::settings::shs_ID_t ID = 0, const shs::SensorType stype = shs::SensorType::unknown, const uint8_t pin = A0);

    void setup() override;
    shs::settings::shs_float_t getValueF() override;
    shs::settings::shs_double_t getValueD() override;
    int16_t getValueI() override;

    shs::settings::shs_float_t getAverageF() override;
    shs::settings::shs_double_t getAverageD() override;
    int16_t getAverageI() override;

protected:
    uint8_t m_pin{};
    uint16_t m_getSamplesSum(const uint8_t count = shs::settings::SENSOR_AVERAGE_SAMPLES);
};
