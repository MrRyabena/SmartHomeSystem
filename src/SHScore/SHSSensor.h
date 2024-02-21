#pragma once
#include <stdint.h>

namespace shs
{
    class Sensor;
    enum SensorType;
};

class shs::Sensor
{
public:
    shs::SensorType type{};
    explicit Sensor(const int16_t ID = 0, const shs::SensorType stype);

    inline void setID(int16_t ID);
    inline int16_t getID();

    inline virtual void begin();

    virtual float getValue();
    virtual double getValue();
    virtual int16_t getValue();

    virtual float getAverage();
    virtual double getAverage();
    virtual int16_t getAverage();

protected:
    int16_t _ID{};
};
