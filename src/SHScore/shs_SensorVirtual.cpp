#include "shs_SensorVirtual.h"


shs::SensorVirtual::SensorVirtual(shs::t::shs_ID_t thisID, shs::t::shs_ID_t virtualID, shs::DTP& dtp, const shs::Sensor::Type stype, const uint32_t expiration_time)
    : Sensor(stype), API(thisID.setComponentID(shs::constants::APIids::Sensor)),
    m_virtualID(virtualID.setComponentID(shs::constants::APIids::Sensor)), m_dtp(dtp),
    m_data(expiration_time)
{}



shs::DTPpacket shs::SensorVirtual::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case shs::Sensor_API::Commands::DATA:
            {
                shs::t::shs_fixed_t data;
                it.get(data);
                m_data.update(data);
            }
            break;

        default:
            break;
    }

    return shs::DTPpacket();
}


void shs::SensorVirtual::update()
{
    if (!isUpdated()) updateForced();
}


void shs::SensorVirtual::updateFast()
{
    update();
}


void shs::SensorVirtual::updateForced([[maybe_unused]] const bool fast)
{
    shs::ByteCollector<> bc(2);
    bc.push_back(shs::Sensor_API::Commands::REQUEST_DATA, 1);
    bc.push_back(true, 1);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_virtualID, std::move(bc)));

    m_data.reset();
}
