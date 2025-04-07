#include "shs_lib_BME280.h"


void shs::BME280::update()
{
    if (!m_data.hasData() || m_data.isExpired()) updateForced();
}


void shs::BME280::updateForced(bool fast)
{
    m_data.update({ bme.readPressure(), bme.readTemperature(), bme.readHumidity() });

    if (m_data.hasData() == false) { m_status = Status::CACHE_ERROR; return; }
    if (isnan(m_data->temperature) || isnan(m_data->humidity)) { m_status = Status::FAILED_READ; return; }
    m_status = Status::OK;
}


shs::t::shs_float_t shs::BME280::getValueF(const uint8_t metric)
{
    if (m_status != Status::OK || !m_data.hasData()) return 0;

    switch (metric)
    {
        case shs::etoi(Metrics::PRESSURE_BAR): return m_data->pressure; break;
        case shs::etoi(Metrics::PRESSURE_MmHg): return pressureToMmHg(m_data->pressure); break;
        case shs::etoi(Metrics::HUMIDITY): return m_data->humidity; break;
        case shs::etoi(Metrics::TEMPERATURE): return m_data->temperature; break;

        default: return 0; break;
    }
    return 0;
}
