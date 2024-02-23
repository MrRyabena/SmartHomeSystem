#include "SHSSensorAnalog.h"

shs::SensorAnalog::SensorAnalog(const shs::settings::shs_ID_t ID, const shs::SensorType stype, const uint8_t pin)
    : ::shs::Sensor(ID, stype), m_pin(pin) {}

void shs::SensorAnalog::setup() { pinMode(_pin, INPUT); }

int16_t shs::SensorAnalog::getValueI() { return analogRead(m_pin); }
shs::settings::shs_float_t shs::SensorAnalog::getValueF() { return static_cast<shs::settings::shs_float_t>(analogRead(m_pin)); }
shs::settings::shs_double_t shs::SensorAnalog::getValueD() { return static_cast<shs::settings::shs_double_t>(analogRead(m_pin)); }

int16_t shs::SensorAnalog::getAverageI()
{
    return static_cast<int16_t>(m_getSamplesSum() / shs::settings::SENSOR_AVERAGE_SAMPLES);
}

shs::settings::shs_float_t shs::SensorAnalog::getAverageF()
{
    return (shs::shs_float_t)m_getSamplesSum() / shs::settings::SENSOR_AVERAGE_SAMPLES;
}

shs::settings::shs_double_t shs::SensorAnalog::getAverageD()
{
    return (shs::shs_double_t)m_getSamplesSum() / shs::settings::SENSOR_AVERAGE_SAMPLES;
}

uint16_t shs::SensorAnalog::m_getSamplesSum(const uint8_t count)
{
    uint16_t aver{};
    for (uint8_t i = 0; i < count; i++)
        aver += analogRead(m_pin);
    return aver;
}
