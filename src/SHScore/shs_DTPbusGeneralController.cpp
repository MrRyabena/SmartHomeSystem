#include "shs_DTPbusGeneralController.h"

#ifndef SHS_SF_AVR

shs::DTPbusGeneralController::DTPbusGeneralController(shs::t::shs_time_t request_timeout,
    shs::t::shs_time_t offline_timeout,
    shs::t::shs_time_t unused_timeout)
    : m_request_timer(request_timeout), m_offline_timeout(offline_timeout),
    m_unused_timeout(unused_timeout)
{}

void shs::DTPbusGeneralController::controlBus(std::shared_ptr<shs::DTPbus> bus)
{
    s_controlBus(bus, m_offline_timeout, m_request_timer.getTimeout(), m_unused_timeout, shs::DTPbusPolicy::UNKNOWN_POLICY);
}

void shs::DTPbusGeneralController::s_controlBus(std::shared_ptr<shs::DTPbus> bus, shs::t::shs_time_t offline_timeout, shs::t::shs_time_t request_timeout, shs::t::shs_time_t unused_timeout, shs::DTPbusPolicy policy)
{
    using BusStatus = shs::DTPbusStatus;
    using Policy = shs::DTPbusPolicy;

    if (!bus) return;

    auto current_policy = m_getPolicy(bus, policy);
    if (current_policy == Policy::UNKNOWN_POLICY || current_policy == Policy::STATIC_BUS) return;

    if (bus->status == BusStatus::packet_received || bus->status == BusStatus::packet_processed)
    {
        switch (current_policy)
        {
            case Policy::TEMPORARY_IF_NO_ANSWERS: [[fallthrough]];
            case Policy::TEMPORARY_IF_DISCONNECTED:
                {
                    if (bus->millisecondsSinceLastReceive() > request_timeout)
                    {
                        bus->sendPacket(shs::DTP_API::getConnectionRequestPacket(bus->busID));
                    }
                    if (bus->millisecondsSinceLastReceive() > offline_timeout)
                    {
                        switch (m_getPolicy(bus, policy))
                        {
                            case shs::DTPbusPolicy::TEMPORARY_IF_NO_ANSWERS:
                                bus->stop();
                                bus->status = BusStatus::bus_error;
                                bus->setActive(false);
                                break;
                        }
                    }
                }
                break;
            case Policy::TEMPORARY_IF_UNUSED:
                {
                    if (bus->millisecondsSinceLastReceive() > unused_timeout)
                    {
                        bus->stop();
                        bus->status = BusStatus::bus_error;
                        bus->setActive(false);
                    }
                }
                break;
        }
    }
}

shs::DTPbusPolicy shs::DTPbusGeneralController::m_getPolicy(std::shared_ptr<shs::DTPbus> bus, shs::DTPbusPolicy policy) noexcept
{
    if (policy == shs::DTPbusPolicy::UNKNOWN_POLICY && bus) return bus->getPolicy();
    return policy;
}


#endif  // #ifndef SHS_SF_AVR
