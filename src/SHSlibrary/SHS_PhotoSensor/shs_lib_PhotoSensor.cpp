#include "shs_lib_PhotoSensor.h"

#include "shs_lib_SensorTypes.h"

#include <shs_SensorAnalog.h>


/**
 * @brief Constructs a PhotoSensor object with the specified analog pin and sample count.
 * 
 * Initializes the sensor for reading analog data from the given pin.
 * Calibration bounds are not set in this constructor.
 * 
 * @param pin analog pin connected to the photoresistor.
 * @param samples number of samples to average for each reading.
 */
shs::PhotoSensor::PhotoSensor(const shs::t::shs_pin_t pin, const uint8_t samples)
    :
    Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::PhotoSensor)),
    SensorAnalog(pin, samples)
{}


/**
 * @brief Constructs a PhotoSensor object with calibration bounds.
 * 
 * Initializes the sensor for reading analog data from the given pin and sets
 * the lower and upper calibration bounds for light intensity.
 * 
 * @param pin analog pin connected to the photoresistor.
 * @param lower_bound lower calibration bound for sensor readings.
 * @param upper_bound upper calibration bound for sensor readings.
 * @param samples number of samples to average for each reading.
 * 
 * @note If @p lower_bound is greater than or equal to @p upper_bound, both bounds are set to 0.
 */
shs::PhotoSensor::PhotoSensor(const shs::t::shs_pin_t pin, const uint16_t lower_bound, const uint16_t upper_bound, const uint8_t samples)
    :
    Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::PhotoSensor)),
    SensorAnalog(pin, samples),
    m_lower_bound(lower_bound), m_upper_bound(upper_bound)
{}


/**
 * @brief Sets the lower and upper calibration bounds for the sensor.
 * 
 * Updates the calibration range for light intensity measurements.
 * If @p lower_bound is greater than or equal to @p upper_bound, both bounds are set to 0.
 * 
 * @param lower_bound Lower calibration bound.
 * @param upper_bound Upper calibration bound.
 */
void shs::PhotoSensor::setBounds(uint16_t lower_bound, uint16_t upper_bound)
{
    if (lower_bound >= upper_bound)
    {
        m_lower_bound = m_upper_bound = 0;
    }

    m_lower_bound = lower_bound;
    m_upper_bound = upper_bound;
}
