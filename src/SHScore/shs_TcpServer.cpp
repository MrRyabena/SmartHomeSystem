#include "shs_TcpServer.h"


void shs::TcpServer::tick()
{
    if (m_connecting_client && m_connecting_client->client.connected())
    {
        if (shs::ProgramTime::s_milliseconds() - m_connecting_client_time > max_connection_time)
        {
            m_connecting_client->stop();
            return;
        }


        if (m_connecting_client->checkBus() != shs::DTPbus::packet_received && m_connecting_client->status != shs::DTPbus::packet_processed) return;


        if (shs::DTPpacket::get_DTPcode(m_connecting_client->getLastData()) == shs::DTPpacket::DTPcode::INITIAL_ANSWER)
        {
            auto answer = shs::DTP_APIpackets::getInitialAnswerPacket(m_dtp.moduleID, true);

            m_connecting_client->sendPacket(answer);

            m_dtp.attachBus(std::move(m_connecting_client));
        }
        else
        {
            m_connecting_client->sendPacket(shs::DTP_APIpackets::getInitialAnswerPacket(m_dtp.moduleID, false));
            m_connecting_client->stop();
        }
    }

    if (server.hasClient())
    {
        m_connecting_client = std::make_unique<shs::TcpSocket>(server.available(), 0, nullptr, 25, nullptr, [this](shs::TcpSocket& socket) { m_dtp.detachBus(socket.busID); });

        m_connecting_client_time = shs::ProgramTime::s_milliseconds();

        auto mes = shs::DTP_APIpackets::getInitialPacket(m_dtp.moduleID);
        m_connecting_client->sendPacket(mes);
    }
}
