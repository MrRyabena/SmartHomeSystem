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
    enum SensorType : uint8_t;
    class Sensor;  
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

    virtual int16_t getValueI(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID = 0) = 0;

    virtual int16_t getAverageI(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID = 0) = 0;

protected:
    shs::settings::shs_ID_t m_ID{};
};
