#include "shs_TcpServer.h"

#if defined(SHS_SF_NETWORK) && defined(SHS_SF_ARDUINO)

#define SHS_SF_DEBUG
#include "shs_debug.h"
void shs::TcpServer::tick()
{
    if (m_connecting_client && m_connecting_client->client.connected())
    {
        doutln("client connected");
        if (shs::ProgramTime::s_milliseconds() - m_connecting_client_time > max_connection_time)
        {
            doutln("max_connection_time exceeded");
            m_connecting_client->stop();
            return;
        }


        if (m_connecting_client->checkBus() != shs::DTPbus::packet_received && m_connecting_client->status != shs::DTPbus::packet_processed) 
        {
            doutln("waiting for INITIAL_ANSWER or INITIAL packet");
            return;
        }
        else
        {
            doutln("data received from client");
        }

        // if (shs::DTPpacket::get_DTPcode(m_connecting_client->getLastData()) == shs::DTPpacket::DTPcode::INITIAL_ANSWER || shs::DTPpacket::get_DTPcode(m_connecting_client->getLastData()) == shs::DTPpacket::DTPcode::INITIAL)
        // {
            //doutln("INITIAL_ANSWER received");
            auto answer = shs::DTP_APIpackets::getInitialAnswerPacket(m_dtp.moduleID, true);

            m_connecting_client->sendPacket(answer);
    
            m_dtp.attachBus(std::move(m_connecting_client));
            doutln("client attached to DTP");
        // }
        // else
        // {
        //     doutln("not INITIAL_ANSWER or INITIAL packet, disconnecting client");
        //     auto it = m_connecting_client->getLastData(); 
        //     for (auto i = 0; i < it.size(); i++) doutln(int(it[i]));
        //     m_connecting_client->sendPacket(shs::DTP_APIpackets::getInitialAnswerPacket(m_dtp.moduleID, false));
        //     m_connecting_client->stop();
        // }
    }

    if (server.hasClient())
    {
        doutln("new client connecting");
        auto client = server.available();
        if (!client) return;
        m_connecting_client = std::make_unique<shs::TcpSocket>(client, m_dtp.getUniqueBusID(), nullptr, 25, nullptr, [this](shs::TcpSocket& socket) { socket.setActive(false); doutln("client unactive"); });

        m_connecting_client_time = shs::ProgramTime::s_milliseconds();

        doutln("sending INITIAL packet");
        auto mes = shs::DTP_APIpackets::getInitialPacket(m_dtp.moduleID);
        doutln("sending packet:");
        m_connecting_client->sendPacket(mes);
        doutln("packet sent");
    }
}

#endif  // #ifdef SHS_SF_NETWORK
