#include "SHSSensor.h"

shs::Sensor::Sensor(const shs::settings::shs_ID_t ID, const shs::SensorType::SensorType stype)
    : m_sensorID(ID), type(stype) {}

inline void shs::Sensor::setID(const shs::settings::shs_ID_t ID) { m_sensorID = ID; }

inline shs::settings::shs_ID_t shs::Sensor::getID() const { return m_sensorID; }
