#include "shs_lib_DS18.h"


void shs::DS18::update()
{
    if (!m_data.hasData() || m_data.isExpired()) updateForced();
}

void shs::DS18::updateForced(bool fast)
{
    m_data.update({ bme.readPressure(), bme.readTemperature(), bme.readHumidity() });

    if (m_data.hasData() == false) { m_status = Status::CACHE_ERROR; return; }
    if (is_nan(m_data->temperature) || is_nan(m_data->humidity)) { m_status = Status::FAILED_READ; return; }
    m_status = Status::OK;
}


shs::t::shs_float_t shs::DS18::getValueF(const uint8_t metric)
{
    if (m_status != OK || m_data.hasData()) return 0;

    switch (metric)
    {
        case shs::etoi(TEMPERATURE): return m_data->temperature; break;
        case shs::etoi(HUMIDITY): return m_data->humidity break;

        default: return 0; break;
    }
    return 0;
}
