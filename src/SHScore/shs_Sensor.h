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
*/

#include <stdint.h>

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_SimpleFixed.h"


namespace shs
{
    class Sensor;
}


/*
    Abstract class for the sensor interface.
*/
class shs::Sensor
{
public:
    enum Type : uint16_t
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

    virtual void update() = 0;
    virtual void updateFast() = 0;
    [[nodiscard]] virtual bool isUpdated() = 0;
    [[nodiscard]] virtual uint8_t getStatus() = 0;

    [[nodiscard]] virtual int32_t              getValueI(const uint8_t metric = 0) = 0;
    [[nodiscard]] virtual shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) = 0;
    [[nodiscard]] virtual shs::t::shs_float_t  getValueF(const uint8_t metric = 0) = 0;
    [[nodiscard]] virtual shs::t::shs_double_t getValueD(const uint8_t metric = 0) = 0;
};
