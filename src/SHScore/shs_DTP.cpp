#include "shs_DTP.h"


shs::DTPbus* shs::DTP::findBusFromModule(const uint8_t moduleID) const
{
    if (moduleID == 0) return nullptr;

    for (auto& bus : m_buss)
        if (bus->connected_modules.get(moduleID) != bus->connected_modules.end()) return bus.get();

    return nullptr;
}


void shs::DTP::tick()
{
    for (auto& bus : m_buss)
    {
        if (!bus->isActive()) { detachBus(bus->busID); return; }

        // if the data is fully received and ready for processing 
        if (bus->checkBus() == shs::DTPbus::packet_processed || bus->status == shs::DTPbus::packet_received)
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

                default: [[fallthrough]];
                case shs::DTPpacket::FAST: break;
            }
        }
        bus->tick();    // update bus
    }
}


shs::t::shs_busID_t shs::DTP::getUniqueBusID() const
{
    if (m_buss.size() == 0) return 1;
    shs::t::shs_busID_t newID = (*m_buss.rbegin())->busID;

    while (m_buss.get(++newID) != m_buss.end());

    return newID;
}
