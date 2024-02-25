#include "SHSLoadAPI.h"

shs::LoadAPIvirtual::LoadAPIVirtual(const shs::settings::shs_ID_t ID, const shs::LoadType type, shs::DTP *dtp)
    : ::shs::API(ID, to, dtp), ::shs::Load(ID, type) {}

void shs::LoadAPIvirtual::on(const uint8_t value, const uint8_t smoothing, const shs::settings::shs_ID_t ID)
{
    shs::ByteCollector bc(shs::LoadAPIcmds::size);
    bc.add(ID, 2);
    bc.add(shs::LoadAPIcmds::on8, 1);
    bc.add(value, 1);
    bc.add(smoothing, 1);
    dtp->sendPacket(&bc, m_to, m_ID);
}
