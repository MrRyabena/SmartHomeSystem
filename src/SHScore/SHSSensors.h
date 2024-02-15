#pragma once
#include <stdint.h>
#include <Arduino.h>

namespace shs
{
    class Sensor;
    class AnalogSensor;
    class DigitalSensor;
};

class shs::Sensor
{
public:
    Sensor(int16_t ID = 0);

    void setID(int16_t ID);
    int16_t getID();

    void begin();

    float getValue();
    double getValue();
    int16_t getValue();

    float getAverage();
    double getAverage();
    int16_t getAverage();

protected:
    int16_t m_ID{};
};

class shs::AnalogSensor : public shs::Sensor
{
public:
    AnalogSensor(int16_t ID = 0, uint8_t pin = 0);
    
    void begin();
    float getValue();
    double getValue();
    int16_t getValue();

    float getAverage();
    double getAverage();
    int16_t getAverage();
    

protected:
    uint8_t m_pin{};
};
