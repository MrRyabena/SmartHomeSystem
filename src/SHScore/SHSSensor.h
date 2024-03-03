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
#include "SHSsettings_private.h"

namespace shs
{
    namespace SensorType
    {
        enum SensorType : uint8_t;
    };
    class Sensor;
};

enum shs::SensorType::SensorType : uint8_t
{
    unknown,
    analogPin,
    thermistor,
    photoresistor,
};

class shs::Sensor
{
public:
    shs::SensorType::SensorType type{};

public:
    explicit Sensor(const shs::settings::shs_ID_t ID = 0, const shs::SensorType::SensorType stype = shs::SensorType::unknown);

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
    shs::settings::shs_ID_t m_sensorID{};
};
