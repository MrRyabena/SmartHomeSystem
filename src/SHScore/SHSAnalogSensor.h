#pragma once

//#include <
#include "SHSSensor.h"

namespace shs {
   class AnalogSensor;  
};

class shs::AnalogSensor : public shs::Sensor
{
public:
    AnalogSensor(const int16_t ID = 0, const shs::SensorType stype, const uint8_t pin = 0);
    
    void begin();
    float getValue();
    double getValue();
    int16_t getValue();

    float getAverage();
    double getAverage();
    int16_t getAverage();
    

protected:
    uint8_t _pin{};
};
