#include "shs_lib_DHT.h"


void shs::DHT::update()
{
    if (!m_data.hasData() || m_data.isExpired()) updateForced();
}


void shs::DHT::updateForced(bool fast)
{
    m_data.update({ m_dht.readTemperature(), m_dht.readHumidity() });

    if (m_data.hasData() == false) { m_status = Status::CACHE_ERROR; return; }
    if (isnan(m_data->temperature) || isnan(m_data->humidity)) { m_status = Status::FAILED_READ; return; }
    m_status = Status::OK;
}


shs::t::shs_float_t  shs::DHT::getValueF(const uint8_t metric)
{
    if (m_data.hasData() == false) { m_status = Status::NO_DATA; return 0; }

    m_status = Status::OK;

    switch (metric)
    {
        case shs::etoi(Metrics::TEMPERATURE): return m_data->temperature; break;
        case shs::etoi(Metrics::HUMIDITY):    return m_data->humidity;    break;
        default: return 0; break;
    }

    return 0;
}
