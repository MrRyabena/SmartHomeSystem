#include "SHSSensor.h"

shs::Sensor::Sensor(const int16_t ID, const shs::SensorType stype)
 : _ID(ID), type(stype) {}

void shs::Sensor::setID(int16_t ID) { _ID = ID; }

int16_t shs::Sensor::getID() { return _ID; }
