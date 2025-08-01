#include "shs_Sensor_API.h"


void shs::Sensor_API::tick()
{
    if (!m_requestIDs.empty())
    {
        shs::ByteCollector<> data(5);
        data.push_back(Commands::DATA, 1);
        data.push_back(m_sensor.getValueFx(), 4);

        for (auto id : m_requestIDs)
            m_dtp.sendPacket(shs::DTPpacket(API_ID, id, data));

        m_requestIDs.clear();
        m_requestIDs.shrink_to_fit();
    }
}


shs::DTPpacket shs::Sensor_API::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    shs::ByteCollector<> data(5);

    switch (it.read())
    {
        [[unlikely]]
        case GET_TYPE:
            {
                data.push_back(Commands::TYPE, 1);
                data.push_back(m_sensor.type, 1);
            }
            break;

            [[likely]]
        case REQUEST_DATA:
            {
                it.read() ? m_sensor.updateFast() : m_sensor.update();

                if (m_sensor.isUpdated())
                {
                    data.push_back(Commands::DATA, 1);
                    data.push_back(m_sensor.getValueFx());
                }

                else
                {
                    m_requestIDs.push_back(shs::DTPpacket::get_senderID(it));
                }
            }
            break;

        default:
            return std::move(shs::DTPpacket());
            break;
    }

    return std::move(shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(data)));
}
