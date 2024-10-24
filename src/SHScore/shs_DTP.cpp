#include "shs_DTP.h"


void shs::DTP::tick()
{
    for (auto& bus : m_buss)
    {
        if (bus->checkBus() == shs::DTPbus::packet_processed)
        {
            auto it = bus->getLastData();
            auto output = m_APIs.get(shs::DTPpacket::get_recipientID(it))->handle(it);
            if (!output.empty()) bus->sendPacket(output);
        }
    }
}
