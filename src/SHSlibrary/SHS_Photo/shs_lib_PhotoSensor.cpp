#include "shs_lib_PhotoSensor.h"

#include "shs_lib_SensorTypes.h"

#include <shs_SensorAnalog.h>


shs::PhotoSensor::PhotoSensor(const shs::t::shs_pin_t pin, const uint8_t samples)
    :
    Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::PhotoSensor)),
    SensorAnalog(pin, samples)
{}


shs::PhotoSensor::PhotoSensor(const shs::t::shs_pin_t pin, const uint16_t floor_bound, const uint16_t ceil_bound, const uint8_t samples)
    :
    Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::PhotoSensor)),
    SensorAnalog(pin, samples),
    m_floor_bound(floor_bound), m_ceil_bound(ceil_bound)
{}


void shs::PhotoSensor::setBounds(uint16_t floor_bound, uint16_t ceil_bound)
{
    if (floor_bound >= ceil_bound)
    {
        m_floor_bound = m_ceil_bound = 0;
    }

    m_floor_bound = floor_bound;
    m_ceil_bound = ceil_bound;
}
