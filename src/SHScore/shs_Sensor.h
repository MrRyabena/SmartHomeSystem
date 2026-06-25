#pragma once

/*
  Last update: v2.0.0
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
      - Caching support.
    v2.3.0 — updated docs.
*/

#include <stdint.h>

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_SimpleFixed.h"


namespace shs
{
    class Sensor;
}


/**
 * @brief Abstract sensor interface with setup, update, cache, and typed value accessors.
 */
class shs::Sensor
{
public:
    /**
     * @brief Defines the sensor family used by derived implementations.
     */
    enum Type : uint16_t
    {
        UNKNOWN,
        ANALOG_PIN,
        THERMISTOR,
        PHOTORESISTOR,
        DIGITAL,
        ANALOG_MAPPED,

        LIBRARY_TYPES = 16384,
        USER_TYPES = 32768,
    }
    const type
        ;

    /**
     * @brief Creates a sensor with the specified sensor type.
     */
    explicit Sensor(const Type stype = UNKNOWN) : type(stype) {}

    /**
     * @brief Releases the sensor interface.
     */
    virtual ~Sensor() = default;


    /**
     * @brief Performs hardware or backend initialization for the sensor.
     */
    virtual void setup() = 0;

    /**
     * @brief Updates the sensor reading using the default accuracy mode.
     */
    virtual void update() = 0;

    /**
     * @brief Updates the sensor reading using the faster, less accurate mode.
     */
    virtual void updateFast() = 0;

    /**
     * @brief Forces a sensor update and optionally uses the fast mode.
     * @param fast If true, uses the faster update method (like updateFast()) if supported by the sensor.
     */
    virtual void updateForced(bool fast = false) = 0;

    /**
     * @brief Reports whether the sensor has a fresh reading available.
     * @return True if the sensor value is updated and can be read, false otherwise.
     */
    [[nodiscard]] virtual bool isUpdated() = 0;

    /**
     * @brief Returns the current sensor status code.
     */
    [[nodiscard]] virtual uint8_t getStatus() = 0;


    /**
     * @brief Clears any cached sensor value, if caching is supported.
     */
    virtual void clearCache() = 0;

    /**
     * @brief Sets the cache lifetime if caching is supported.
     * @param expiration_time Cache expiration time in milliseconds.
     */
    virtual void setCacheExpiration(const uint32_t expiration_time) = 0;

    /**
     * @brief Returns the configured cache lifetime.
     * @return Cache expiration time in milliseconds.
     */
    virtual uint32_t getCacheExpiration() const = 0;


    /**
     * @brief Returns the sensor value as a signed integer.
     * @param metric Optional metric index for sensors that support multiple metrics. Default is 0.
     * @return The sensor value converted to int32_t according to the specified metric.
     */
    [[nodiscard]] virtual int32_t              getValueI(const uint8_t metric = 0) = 0;

    /**
     * @brief Returns the sensor value as a fixed-point number.
     * @param metric Optional metric index for sensors that support multiple metrics. Default is 0.
     * @return The sensor value converted to shs_fixed_t according to the specified metric.
     */
    [[nodiscard]] virtual shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) = 0;

    /**
     * @brief Returns the sensor value as a floating-point number.
     * @param metric Optional metric index for sensors that support multiple metrics. Default is 0.
     * @return The sensor value converted to shs_float_t according to the specified metric.
     */
    [[nodiscard]] virtual shs::t::shs_float_t  getValueF(const uint8_t metric = 0) = 0;

    /**
     * @brief Returns the sensor value as a double-precision number.
     * @param metric Optional metric index for sensors that support multiple metrics. Default is 0.
     * @return The sensor value converted to shs_double_t according to the specified metric.
     */
    [[nodiscard]] virtual shs::t::shs_double_t getValueD(const uint8_t metric = 0) = 0;
};
