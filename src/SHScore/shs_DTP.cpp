#include "shs_DTP.h"


void shs::DTP::tick()
{
    for (auto& bus : m_buss)
    {
        if (bus->checkBus() == shs::DTPbus::packet_processed)
        {
            auto it = bus->getLastData();
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
    }
}
