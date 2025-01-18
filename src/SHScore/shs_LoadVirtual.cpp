#include "shs_LoadVirtual.h"


void shs::LoadVirtual::on(const uint8_t value)
{
    shs::ByteCollector<> bc(2);
    bc.push_back(Commands::ON8, 1);
    bc.push_back(value, 1);

    m_dtp.sendPacket(std::move(shs::DTPpacket(bc)));
}


void shs::LoadVirtual::on(const uint16_t value)
{
    shs::ByteCollector<> bc(3);
    bc.push_back(Commands::ON16, 1);
    bc.push_back(value, 2);

    m_dtp.sendPacket(std::move(shs::DTPpacket(bc)));
}


void shs::LoadVirtual::off()
{
    shs::ByteCollector<> bc(1);
    bc.push_back(Commands::OFF, 1);

    m_dtp.sendPacket(std::move(shs::DTPpacket(bc)));
}
