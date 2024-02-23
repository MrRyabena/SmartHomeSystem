#pragma once

/*
  Abstract class for the sensor interface.
*/
/*
  Last update: v1.2.0
  Versions:
    v1.1.0 — created.
    v1.2.0 — made purely virtual.
*/

#include <stdint.h>
#include "SHSsettings_private.h"

namespace shs
{
    class Sensor;
    enum SensorType;
};

enum shs::SensorType : uint8_t
{
    unknown,
    analogPin,
    thermistor,
    photoresistor,
};

class shs::Sensor
{
public:
    shs::SensorType type{};

public:
    explicit Sensor(const shs::settings::shs_ID_t ID = 0, const shs::SensorType stype = shs::SensorType::unknown);

    void setID(const shs::settings::shs_ID_t ID);
    shs::settings::shs_ID_t getID() const;

    virtual void setup() = 0;

    virtual int16_t getValueI() = 0;
    virtual shs::settings::shs_float_t getValueF() = 0;
    virtual shs::settings::shs_double_t getValueD() = 0;

    virtual int16_t getAverageI() = 0;
    virtual shs::settings::shs_float_t getAverageF() = 0;
    virtual shs::settings::shs_double_t getAverageD() = 0;

protected:
    shs::settings::shs_ID_t m_ID{};
};
