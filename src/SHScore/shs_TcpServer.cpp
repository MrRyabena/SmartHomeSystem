#include "shs_TcpServer.h"

#if defined(SHS_SF_NETWORK) && defined(SHS_SF_ARDUINO)

#include "shs_DTPbusReceiveStatus.h"
#include "shs_debug.h"


void shs::TcpServer::tick()
{
    if (m_connecting_client)
    {

        if (shs::ProgramTime::s_milliseconds() - m_connecting_client_time > max_connection_time)
        {
            m_connecting_client->stop();
            doutln("Connection timeout, closing client");
            return;
        }

        using ReceiveStatus = shs::DTPbusReceiveStatus;
        if (m_connecting_client->checkBus() != ReceiveStatus::packet_received && m_connecting_client->getReceiveStatus() != ReceiveStatus::packet_processed)
        {
            doutln("Waiting for initial packet from client...");
            return;
        }
        else
        {
            auto answer = shs::DTP_API::getInitialAnswerPacket(m_dtp.moduleID, true);
            m_connecting_client->sendPacket(answer);

            auto id = m_dtp.attachBus(std::move(m_connecting_client));
            dout("Client connected, bus ID: ");
            doutln(static_cast<int>(id));

            m_connecting_client.reset();

            return;
        }
    }

    else if (server.hasClient())
    {
        auto client = server.available();
        if (!client) return;

        m_connecting_client = std::make_unique<shs::TcpSocket>(client, m_dtp.getUniqueBusID(), nullptr, 25, nullptr, [this](shs::TcpSocket& socket) { socket.setActive(false); });
        m_connecting_client->setConnectingTimeout(max_connection_time);
        m_connecting_client->setReconnectingTimeout(0);

        m_connecting_client_time = shs::ProgramTime::s_milliseconds();
        m_connecting_client->start();

        auto mes = shs::DTP_API::getInitialPacket(m_dtp.moduleID);
        m_connecting_client->sendPacket(mes);

        dfunc();
        dout("New client connected, waiting for initial packet, IP: ");
        doutln(m_connecting_client->getIP().toString());

    }
}

#endif  // #ifdef SHS_SF_NETWORK
