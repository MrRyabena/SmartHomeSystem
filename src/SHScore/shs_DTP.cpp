#include "shs_DTP.h"


void shs::DTP::tick()
{
    for (auto& bus : m_buss)
    {
        // if the data is fully received and ready for processing 
        if (bus->checkBus() == shs::DTPbus::packet_processed)
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
                    }
                    break;

                default: [[fallthrough]]
                case shs::DTPpacket::FAST:
                    break;

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
