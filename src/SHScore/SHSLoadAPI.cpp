#include "SHSLoadAPI.h"

shs::LoadAPIvirtual::LoadAPIvirtual(const shs::settings::shs_ID_t ID, const shs::settings::shs_ModuleID_t to)
    : ::shs::API(ID, to), ::shs::Load(ID) {}

void shs::LoadAPIvirtual::on(const uint8_t value, const uint8_t smoothing, const shs::settings::shs_ID_t ID)
{
    shs::ByteCollector bc(5);
    bc.add(ID, 2);
    bc.add(shs::LoadAPIcmds::Lon8, 1);
    bc.add(value, 1);
    bc.add(smoothing, 1);

    shs::module.sendPacket(&bc, m_to, m_apiID);
}

void shs::LoadAPIvirtual::on(const uint16_t value, const uint16_t smoothing, const shs::settings::shs_ID_t ID)
{
    shs::ByteCollector bc(7);
    bc.add(ID, 2);
    bc.add(shs::LoadAPIcmds::Lon16, 1);
    bc.add(value, 2);
    bc.add(smoothing, 2);

    shs::module.sendPacket(&bc, m_to, m_apiID);
}

void shs::LoadAPIvirtual::off(const uint16_t smoothing, const shs::settings::shs_ID_t ID)
{
    shs::ByteCollector bc(5);
    bc.add(ID, 2);
    bc.add(shs::LoadAPIcmds::Loff, 1);
    bc.add(smoothing, 2);

    shs::module.sendPacket(&bc, m_to, m_apiID);
}

shs::LoadAPIhandler::LoadAPIhandler(const shs::settings::shs_ID_t ID,
                                    const shs::settings::shs_ModuleID_t to, shs::Load *loads)
    : ::shs::API(ID, to), m_loads(loads) {}

uint8_t shs::LoadAPIhandler::handler(shs::ByteCollector &data)
{
    data.readPtr = data.buf + 3;
    shs::settings::shs_ID_t apiID{};
    data.get(apiID, 2);
    if (apiID != m_apiID)
        return shs::errors::DTP_INVALIDaddress;
    if (!m_loads)
        return shs::errors::DTP_PTRerror;

    switch (data.buf[7])
    {
    case shs::LoadAPIcmds::Lon8:
    {
        shs::settings::shs_ID_t ID{};
        data.get(ID, 2);

        m_loads->on(data.buf[8], data.buf[9], ID);
        return 0;
    }
    break;

    case shs::LoadAPIcmds::Lon16:
    {
        uint16_t value{};
        uint16_t smoothing{};
        shs::settings::shs_ID_t ID{};

        data.get(ID, 2);
        data.get(value, 2);
        data.get(smoothing, 2);

        m_loads->on(value, smoothing, ID);
        return 0;
    }
    break;

    case shs::LoadAPIcmds::Loff:
    {
        shs::settings::shs_ID_t ID{};
        uint16_t smoothing{};

        data.get(ID);
        data.get(smoothing);

        m_loads->off(smoothing, ID);

        return 0;
    }
    break;

    default:
        return shs::errors::DTP_CMDerror;
        break;
    }
}
