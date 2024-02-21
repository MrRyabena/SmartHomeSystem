#include "SHSAnalogSensor.h"

shs::AnalogSensor::AnalogSensor(const int16_t ID, const shs::SensorType stype, const uint8_t pin)
    : _ID(ID), type(stype), _pin(pin) {}

void shs::AnalogSensor::begin() { pinMode(_pin, INPUT); }

int16_t shs::AnalogSensor::getValue() { return analogRead(_pin); }
float shs::AnalogSensor::getValue() { return static_cast<float>(analogRead(_pin)); }
double shs::AnalogSensor::getValue() { return static_cast<double>(analogRead(_pin)); }


