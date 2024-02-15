#include "SHSSensors.h"

shs::Sensor::Sensor(int16_t ID) : m_ID(ID) {}

void shs::Sensor::setID(int16_t ID)
{
    m_ID = ID;
}

int16_t shs::Sensor::getID()
{
    return m_ID;
}

shs::AnalogSensor::AnalogSensor(int16_t ID, uint8_t pin) : m_pin(pin)
{
    m_ID = ID;
}

void shs::AnalogSensor::begin()
{
    pinMode(m_pin, INPUT);
}

int16_t shs::AnalogSensor::getValue()
{
    return analogRead(m_pin);
}
