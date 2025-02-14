#pragma once

#include <GyverDS18.h>  // https://github.com/GyverLibs/GyverDS18

#include <shs_Sensor.h>


namespace shs
{
    class GyverDS18_Sensor;
}


class shs::GyverDS18_Sensor : public shs::Sensor
{
public:
    GyverDS18 gds;

    explicit GyverDS18_Sensor(const uint8_t pin, const bool parasite = true) : Sensor(shs::Sensor::Type::DIGITAL), gds(pin, parasite) {}
    
    void setup() override {}




};
