#include "shs_DTP.h"
#include "shs_debug.h"
#ifndef SHS_SF_AVR

#include "shs_DTPbusStatus.h"

uint8_t shs::DTP::sendPacket(const shs::DTPpacket& packet)
{
    if (packet.empty()) return 0;

    auto bus = findBusFromModule(packet.get_recipientID().getModuleID());
    if (bus) return bus->sendPacket(packet);

    // store a copy for later delivery, but ensure proper copy semantics
    shs::DTPpacket packet_copy(packet);
    m_outgoing_packets.push_back(OutgoingPacket(std::move(packet_copy)));
    return 0;
}


shs::t::shs_busID_t shs::DTP::attachBus(std::shared_ptr<shs::DTPbus> bus)
{
    doutln("DTP::attachBus");
    if (bus && (bus->busID == 0 || m_buss.get(bus) != m_buss.end())) bus->busID = getUniqueBusID();
    doutln("set busID");
    return (*m_buss.attach(std::move(bus)))->busID;
}


shs::DTPbus* shs::DTP::findBusFromModule(const uint8_t moduleID) const
{
    if (moduleID == 0) return nullptr;

    for (auto& bus : m_buss)
        if (bus->connected_modules.get(moduleID) != bus->connected_modules.end()) return bus.get();

    return nullptr;
}


void shs::DTP::start()
{
    for (auto& bus : m_buss) bus->start();
#ifdef SHS_SF_NETWORK
    if (m_discover) m_discover->start();
#endif
}


void shs::DTP::tick()
{
    for (auto& bus : m_buss)
    {
        if (!bus) continue;
        if (!bus->isActive()) { detachBus(bus->busID); return; }

        // if the data is fully received and ready for processing 
        using BusStatus = shs::DTPbusStatus;
        if (bus->checkBus() == BusStatus::packet_processed || bus->status == BusStatus::packet_received)
        {
            auto it = bus->getLastData();

            // processing of DTP-code
            switch (shs::DTPpacket::get_DTPcode(it))
            {
                case shs::DTPpacket::STANDARD:
                    {
                        auto id = shs::DTPpacket::get_recipientID(it);
                        auto api = m_APIs.get(id);

                        if (api != m_APIs.end())
                        {
                            auto output = std::move((*api)->handle(it));
                            if (!output.empty()) bus->sendPacket(output);
                        }
                        else
                        {
                            auto api = m_externalAPIs.get(id);
                            if (api != m_externalAPIs.end())
                            {
                                auto output = std::move((*api)->handle(it));
                                if (!output.empty()) bus->sendPacket(output);
                            }
                        }
                    }
                    break;

                case shs::DTPpacket::MASK:
                    {
                        auto id = shs::DTPpacket::get_recipientID(it);
                        auto mask = shs::DTPpacket::get_mask(it);

                        for (auto& api : m_APIs)
                        {
                            if ((api->API_ID & mask) == (id & mask))
                            {
                                auto output = std::move(api->handle(it));
                                if (!output.empty()) bus->sendPacket(output);
                            }
                        }
                    }
                    break;

                case shs::DTPpacket::FAST: [[fallthrough]];
                default: break;

            }
        }
        bus->tick();    // update bus
    }

#ifdef SHS_SF_NETWORK
    if (m_discover) m_discover->tick();
#endif

    if (!m_outgoing_packets.empty())
    {
        auto it = m_outgoing_packets.begin();
        if (it->timer.expired())
        {
            m_outgoing_packets.pop_front();
            return;
        }

        switch (it->status)
        {
            case OutgoingPacket::BusStatus::NOT_FOUND:
                doutln("discover new device");
            #ifdef SHS_SF_NETWORK
                if (m_discover) m_discover->discover(it->packet.get_recipientID().getModuleID());
                it->status = OutgoingPacket::BusStatus::WAITING_FROM_DISCOVER;
            #endif
                break;

            case OutgoingPacket::BusStatus::WAITING_FROM_DISCOVER:
            #ifdef SHS_SF_NETWORK
                if (m_discover)
                {
                    auto ip = m_discover->check(it->packet.get_recipientID().getModuleID());
                    if (ip)
                    {
                        doutln("device discovered!!");
                        auto tcp_bus = std::make_unique<shs::TcpSocket>(ip, shs::settings::DEFAULT_TCP_PORT, getUniqueBusID());
                        tcp_bus->connected_modules.attach(it->packet.get_recipientID().getModuleID());
                        tcp_bus->start();
                        attachBus(std::move(tcp_bus));

                        it->status = OutgoingPacket::BusStatus::DISCOVERED;
                    }
                    else { m_discover->discover(it->packet.get_recipientID().getModuleID()); }
                }
            #endif
                break;

            case OutgoingPacket::BusStatus::DISCOVERED:
                {
                    dout("try to send packet with id: ");
                    auto bus = findBusFromModule(it->packet.get_recipientID().getModuleID());
                    doutln(it->packet.get_recipientID().getModuleID());
                    if (bus)
                    {
                        doutln("send packet to discovered device");
                        bus->sendPacket(it->packet);
                        m_outgoing_packets.pop_front();
                    }
                    else it->status = OutgoingPacket::BusStatus::NOT_FOUND;
                }
                break;

            default:
                break;
        }
    }
}


shs::t::shs_busID_t shs::DTP::getUniqueBusID() const
{
    if (m_buss.size() == 0) return 1;
    shs::t::shs_busID_t newID = (*m_buss.rbegin())->busID;

    while (m_buss.get(++newID) != m_buss.end());

    return newID;
}


#endif    // #ifdef SHS_SF_AVR
