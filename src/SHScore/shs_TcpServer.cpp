#include "shs_TcpServer.h"


void shs::TcpServer::tick()
{
    if (server.hasClient())
    {
        if (server.hasClientData())
        {
            WiFiClient client = server.available();

            uint8_t len{};
            shs::DTPbus::Status status{};
            shs::ByteCollector<> bc(10);


            do status = shs::DTPbus::checkBus(client, bc, len);
            while (status == shs::DTPbus::packet_is_expected); // need timer or async

            if (status != shs::DTPbus::packet_received) return;

            shs::DTPpacket packet(std::move(bc));
            if (packet.get_DTPcode() == shs::DTPpacket::DTPcode::INITIAL)
            {
                auto mes = shs::DTP_APIpackets::getInitialPacket(10);  // need correct id
                client.write(mes.bc.getPtr(), mes.bc.size());
                auto busID = packet.get_senderID();
                m_dtp.attachBus(std::make_unique<shs::TcpSocket>(client, busID, nullptr, 25, [](shs::TcpSocket&) {doutln("connect!");}, [this](shs::TcpSocket& socket) { doutln("disconnect!"); m_dtp.detachBus(socket.busID); }));
            }
        }
    }
}
