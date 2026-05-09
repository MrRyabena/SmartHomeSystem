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
	  - Added parameter 'type' to constructor.
*/

#include "shs_Sensor.h"
#include "shs_types.h"


namespace shs
{
	//  class Sensor;          // declared in shs_Sensor.h
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
    /**
     * @brief Creates an analog sensor reader bound to a single pin.
		* @param pin Hardware pin used for analog reads.
		* @param samples Number of analog samples to average per update.
		* @param type Sensor classification value for this instance.
     */
	explicit SensorAnalog(shs::t::shs_pin_t pin, uint8_t samples = SENSOR_AVERAGE_SAMPLES, Type type = ANALOG_PIN);

    /**
     * @brief Default sample count used for averaging.
     */
	static constexpr uint8_t SENSOR_AVERAGE_SAMPLES = SHS_SET_SENSOR_AVERAGE_SAMPLES;

	/**
	 * @brief Updates the number of samples used for averaging.
	 * @param samples Number of samples to use.
	 */
	void setSamples(const uint8_t samples) { m_samples = samples; }

	/**
	 * @brief Returns the number of samples used for averaging.
	 * @return Current averaging sample count.
	 */
	[[nodiscard]] uint8_t getSamples() const { return m_samples; }

	/**
	 * @brief Initializes the analog input.
	 */
	void setup() override;

	/**
	 * @brief Reads the pin using the standard averaging path.
	 */
	void update() override;

	/**
	 * @brief Reads the pin using the faster update path.
	 */
	void updateFast() override;

	/**
	 * @brief Forces an update using the chosen accuracy mode.
	 * @param fast If true, uses the fast update path.
	 */
	void updateForced(bool fast = false) override { fast ? updateFast() : update(); }

	/**
	 * @brief Reports that the analog sensor value is always current after update.
	 * @return Always true for this implementation.
	 */
	[[nodiscard]] bool isUpdated() override { return true; }

	/**
	 * @brief Returns the current status code.
	 * @return Status code. Returns 0 in this implementation.
	 */
	[[nodiscard]] uint8_t getStatus() override { return 0; }

	/**
	 * @brief Clears the cache. Analog sensors do not keep a separate cache.
	 */
	void clearCache() override {}

	/**
	 * @brief Sets cache expiration. Analog sensors do not cache values.
	 * @param expiration_time Unused cache expiration value in milliseconds.
	 */
	void setCacheExpiration(const uint32_t expiration_time) override {}

	/**
	 * @brief Returns cache expiration. Analog sensors do not cache values.
	 * @return Always 0 for non-cached analog sensors.
	 */
	[[nodiscard]] uint32_t getCacheExpiration() const override { return 0; }

	/**
	 * @brief Returns the current value as a signed integer.
	 * @param metric Metric index. Unused for analog pin sensors.
	 * @return Current analog value converted to int32_t.
	 */
	[[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return static_cast<int32_t>(m_value); }

	/**
	 * @brief Returns the current value as a fixed-point number.
	 * @param metric Metric index. Unused for analog pin sensors.
	 * @return Current analog value converted to shs_fixed_t.
	 */
	[[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return static_cast<shs::t::shs_fixed_t>(m_value); }

	/**
	 * @brief Returns the current value as a floating-point number.
	 * @param metric Metric index. Unused for analog pin sensors.
	 * @return Current analog value as shs_float_t.
	 */
	[[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override { return m_value; }

	/**
	 * @brief Returns the current value as a double-precision number.
	 * @param metric Metric index. Unused for analog pin sensors.
	 * @return Current analog value converted to shs_double_t.
	 */
	[[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(m_value); }

protected:
	/**
	 * @brief Last measured analog value.
	 */
	shs::t::shs_float_t m_value;

	/**
	 * @brief Input pin used for sampling.
	 */
	const shs::t::shs_pin_t m_pin;

	/**
	 * @brief Sample count used for averaging.
	 */
	uint8_t m_samples;
};
