#include "SHSSensor.h"

shs::Sensor::Sensor(const shs::settings::shs_ID_t ID, const shs::SensorType stype)
 : m_ID(ID), type(stype) {}

void shs::Sensor::setID(const shs::settings::shs_ID_t ID) { m_ID = ID; }

shs::settings::shs_ID_t shs::Sensor::getID() const  { return m_ID; }
