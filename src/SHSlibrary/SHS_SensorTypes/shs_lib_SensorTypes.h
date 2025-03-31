#pragma once

#include <stdint.h>

#include <shs_settings_private.h>
#include <shs_Sensor.h>



namespace shs
{
    namespace lib
    {
        enum class SensorTypes : uint16_t;
    }
}


enum class shs::lib::SensorTypes : uint16_t
{
    UNKNOWN = shs::Sensor::Type::UNKNOWN,

    INITIAL_VALUE = shs::Sensor::Type::LIBRARY_TYPES,
    DHT,
    BME280, BMP280,
    MHZ19,
    DS18,
    Thermistor,

    USER_TYPES = shs::Sensor::Type::USER_TYPES
};
