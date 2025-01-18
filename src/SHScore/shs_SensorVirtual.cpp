#include "shs_SensorVirtual.h"



shs::DTPpacket shs::SensorVirtual::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case shs::Sensor_API::Commands::DATA:
            it.get(m_value);
            m_updatedFlag = true;
            break;

        default:
            break;
    }

    return shs::DTPpacket();
}


void shs::SensorVirtual::update()
{
    shs::ByteCollector<> bc(2);
    bc.push_back(shs::Sensor_API::Commands::REQUEST_DATA, 1);
    bc.push_back(false, 1);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_virtualID, std::move(bc)));

    m_updatedFlag = false;
}


void shs::SensorVirtual::updateFast()
{
    shs::ByteCollector<> bc(2);
    bc.push_back(shs::Sensor_API::Commands::REQUEST_DATA, 1);
    bc.push_back(true, 1);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_virtualID, std::move(bc)));

    m_updatedFlag = false;
}


