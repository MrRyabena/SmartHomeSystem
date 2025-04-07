#include "shs_lib_MHZ19.h"


void shs::MHZ19::update()
{
    if (!m_data.hasData() || m_data.isExpired()) updateForced();
}


void shs::MHZ19::updateForced(bool fast)
{
    m_data.update({m_mhz19.getPPM(), m_mhz19.getPPM()});

    if (m_data.hasData() == false) m_status = Status::CACHE_ERROR;
}


uint8_t shs::MHZ19::getStatus()
{
    if (m_mhz19.isWarming()) { m_status = Status::WARMING; return shs::etoi(m_status); }
    if (m_status == Status::CACHE_ERROR) { return shs::etoi(m_status); }

    switch (m_mhz19.getStatus())
    {
        case -1: m_status = Status::NO_RESPONSE;        break;
        case 0:  m_status = Status::UNDEFINED;          break;
        case 64: m_status = Status::HIGH_ACCURACY;      break;
        case 32: m_status = Status::INCREASED_ACCURACY; break;
        case 16: m_status = Status::MEDIUM_ACCURACY;    break;
        case 8:  m_status = Status::REDUCED_ACCURACY;   break;
        case 4:  m_status = Status::LOW_ACCURACY;       break;
        default: m_status = Status::UNDEFINED;          break;
    }

    return shs::etoi(m_status);
}
