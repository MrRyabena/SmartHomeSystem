#include "shs_LoadVirtual.h"


void shs::LoadVirtual::on(const uint16_t value)
{
    shs::ByteCollector<> bc(3);
    bc.push_back(Commands::ON16, 1);
    bc.push_back(value, 2);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_virtualID, std::move(bc)));
}


void shs::LoadVirtual::off()
{
    shs::ByteCollector<> bc(1);
    bc.push_back(Commands::OFF, 1);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_virtualID, std::move(bc)));
}
