#include "shs_DTPbusController.h"


#ifndef SHS_SF_AVR


shs::DTPbusController::DTPbusController(std::weak_ptr<shs::DTPbus> bus, shs::t::shs_time_t offline_timeout,
    shs::t::shs_time_t request_timeout, shs::t::shs_time_t unused_timeout, shs::DTPbusPolicy policy)
    : DTPbusGeneralController(request_timeout, offline_timeout, unused_timeout),
    m_bus(bus), m_policy(policy)
{}

void shs::DTPbusController::start()
{
    m_request_timer.reset();
}

void shs::DTPbusController::tick()
{
    if (!m_request_timer.check()) return;

    if (auto bus = m_bus.lock())
    {
        s_controlBus(bus, m_offline_timeout, m_request_timer.getTimeout());
    }
}


#endif  // #ifndef SHS_SF_AVR
