#include "shs_lib_PhotoSensor.h"

#include "shs_lib_SensorTypes.h"

#include <shs_SensorAnalog.h>


shs::PhotoSensor::PhotoSensor(const shs::t::shs_pin_t pin, const uint8_t samples)
    :
    Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::PhotoSensor)),
    SensorAnalog(pin, samples)
{}


shs::PhotoSensor::PhotoSensor(const shs::t::shs_pin_t pin, const uint16_t lower_bound, const uint16_t upper_bound, const uint8_t samples)
    :
    Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::PhotoSensor)),
    SensorAnalog(pin, samples),
    m_lower_bound(lower_bound), m_upper_bound(upper_bound)
{}


void shs::PhotoSensor::setBounds(uint16_t lower_bound, uint16_t upper_bound)
{
    if (lower_bound >= upper_bound)
    {
        m_lower_bound = m_upper_bound = 0;
    }

    m_lower_bound = lower_bound;
    m_upper_bound = upper_bound;
}
