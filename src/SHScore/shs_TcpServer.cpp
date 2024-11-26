#include "shs_TcpServer.h"


void shs::TcpServer::tick()
{
    if (m_connecting_client)
    {
        if (m_connecting_client_time - shs::ProgramTime::s_microseconds() > max_connection_time)
        {
            m_connecting_client.reset();
            return;
        }

        if (m_connecting_client.checkBus() != shs::DTPbus::packet_received) return;

        if (shs::DTPpacket::get_DTPcode(m_connecting_client.getLastData()) == shs::DTPpacket::DTPcode::INITIAL)
        {
            // need send good callback
            m_dtp.attachBus(std::move(m_connecting_client));
        }
        else
        {
            // need send error callback
        }

    }

    if (server.hasClient())
    {
        m_connecting_client = std::make_unique<shs::TcpSocket>(server.available(), 0, nullptr, 25, [](shs::TcpSocket&) {doutln("connect!");}, [this](shs::TcpSocket& socket) { doutln("disconnect!"); m_dtp.detachBus(socket.busID); });
        m_connecting_client_time = shs::ProgramTime::s_microseconds();
        auto mes = shs::DTP_APIpackets::getInitialPacket(10);  // need correct id
        client.write(mes.bc.getPtr(), mes.bc.size());
    }
}
