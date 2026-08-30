#include "shs_DTPbusController.h"

shs::DTPbusController::DTPbusController(std::weak_ptr<shs::DTPbus> bus, shs::t::shs_time_t offline_timeout,
    shs::t::shs_time_t request_timeout, shs::t::shs_time_t unused_timeout, shs::DTPbusPolicy policy)
    : m_bus(std::move(bus)), m_request_timer(request_timeout), m_offline_timeout(offline_timeout),
    m_unused_timeout(unused_timeout), m_policy(policy)
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
        controlBus(bus, m_offline_timeout, m_request_timer.getTimeout());
    }
}

void shs::DTPbusController::stop()
{}

void shs::DTPbusController::controlBus(std::shared_ptr<shs::DTPbus> bus, shs::t::shs_time_t offline_timeout, shs::t::shs_time_t request_timeout, shs::t::shs_time_t unused_timeout, shs::DTPbusPolicy policy)
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
                     
                    if (bus->millisecondsSinceLast() > unused_timeout)
                    {
                        bus->stop();
                        bus->status = BusStatus::bus_error;
                        bus->setActive(false);
                    }
                }
        }


    }
}

shs::DTPbusPolicy shs::DTPbusController::m_getPolicy(std::shared_ptr<shs::DTPbus> bus, shs::DTPbusPolicy policy) noexcept
{
    if (policy == shs::DTPbusPolicy::UNKNOWN_POLICY && bus) return bus->getPolicy();
    return policy;
}
