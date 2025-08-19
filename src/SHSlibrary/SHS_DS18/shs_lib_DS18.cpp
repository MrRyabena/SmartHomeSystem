#include "shs_lib_DS18.h"



shs::DS18::DS18(const shs::t::shs_pin_t pin, const bool parasite, const uint32_t cache_expiration)
    : Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::DS18)), gds(pin, parasite), m_data(cache_expiration)
{}


void shs::DS18::update()
{
    if (!isUpdated()) updateForced();   
}


void shs::DS18::updateForced(bool fast)
{
    if (!gds.isWaiting()) gds.requestTemp();
    m_status = Status::UPDATING;
}


bool shs::DS18::isUpdated()
{
    if (m_status != Status::UPDATING && m_data.isExpired()) return false;

    if (m_status == Status::UPDATING && gds.ready())
    {
        if (!gds.readTemp()) 
        {
            m_status = Status::FAILED_READ;
            return false;

        }
        m_data.update(gds.getTemp());
        
        if (m_data.hasData() == false) { m_status = Status::CACHE_ERROR; return false; }
        if (isnan(*m_data)) { m_status = Status::FAILED_READ; return false; }
        m_status = Status::OK;
    }

    return true;
}


shs::t::shs_float_t shs::DS18::getValueF(const uint8_t metric)
{
    if (!m_data.hasData()) return 0; // m_status != Status::OK || 
 
    return *m_data;
}
