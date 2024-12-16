#pragma once

/*
    Last update: v1.0.0
    Versions:
        v0.1.0 — created.
        v0.2.0 — made purely virtual.
        v1.0.0 — release.
*/

/*
    Abstract class for the sensor interface.
*/

#include <stdint.h>

#include "shs_settings_private.h"
#include "shs_types.h"


namespace shs
{
    class Sensor;
}


class shs::Sensor
{
public:
    enum Type : uint8_t
    {
        UNKNOWN,
        ANALOG_PIN,
        THERMISTOR,
        PHOTORESISTOR,
        DIGITAL,
        USER_TYPES,
    }
    const type
        ;

    explicit Sensor(const Type stype = UNKNOWN) : type(stype) {}

    virtual ~Sensor() = default;


    virtual void setup() = 0;

    virtual int16_t getValueI() = 0;
    virtual shs::t::shs_float_t getValueF() = 0;
    virtual shs::t::shs_double_t getValueD() = 0;

    virtual int16_t getAverageI() = 0;
    virtual shs::t::shs_float_t getAverageF() = 0;
    virtual shs::t::shs_double_t getAverageD() = 0;

};
