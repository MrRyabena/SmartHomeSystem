#include "shs_DTP.h"


uint8_t shs::DTP::checkBus()
{
    if (m_bus.available() == 0) return Status::no_data;

    if (m_len == 0) m_len = m_bus.read();
    if (m_bus.available() < m_len - 1) return Status::packet_is_expected;

    m_bc.reset();
    m_bc.push_back(m_len, 1);

    for (uint8_t i = 0; i < m_len - 1; i++) m_bc.push_back(m_bus.read(), 1);

    m_len = 0;

    auto it = m_bc.getReadIt();
    m_handler.handle(it);

    return Status::packet_processed;
}