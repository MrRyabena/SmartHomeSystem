#include "shs_TcpServer.h"


void shs::TcpServer::tick()
{
    if (server.hasClient())
    {
        if (server.hasClientData())
        {
            WiFiClient client = server.available();
            uint8_t len = client.read();
            while (client.available() < len - 1);
            shs::ByteCollector<> bc(len);
            bc.push_back(len, 1);
            for (uint8_t i = 0; i < len - 1; i++) bc.push_back(client.read(), 1);

            shs::DTPpacket packet(std::move(bc));
            if (packet.get_DTPcode() == shs::DTPpacket::DTPcode::INITIAL)
            {
                auto mes = shs::DTP_APIpackets::getInitialPacket(10);
                client.write(mes.bc.getPtr(), mes.bc.size());
                auto busID = packet.get_senderID();
                m_dtp.attachBus(std::make_unique<shs::TcpSocket>(client, busID, nullptr, 25, [](shs::TcpSocket&) {doutln("connect!");}, [this](shs::TcpSocket& socket) { doutln("disconnect!"); m_dtp.detachBus(socket.busID); }));
            }
        }
    }
}
