#include "SHSTcpServer.h"

shs::TcpServer::TcpServer(const uint8_t *IPaddress, uint16_t port, uint8_t max_clients)
    : server(WiFiServer(port)),
      clients(new WiFiClient[max_clients]),
      lens(new uint8_t[max_clients]{}),
      IP(IPaddress),
      maxClients(max_clients)

{
    m_dtp_beg = ::operator new(sizeof(shs::DTP));
}

shs::TcpServer::~TcpServer()
{
    delete[] clients;
    delete[] lens;
    ::operator delete(m_dtp_beg);
}

void shs::TcpServer::begin()
{
    server.begin();
    server.setNoDelay(true);
}

void shs::TcpServer::tick()
{
    if (server.hasClient())
    {
        for (i = 0; i < maxClients; i++)
        {
            if (!clients[i] || (clients[i] && !clients[i].connected()))
            {

                if (clients[i])
                    clients[i].stop();
                clients[i] = server.available();
                break;
            }
        }
        WiFiClient client = server.available();
        client.stop();
    }

    for (i = 0; i < maxClients; i++)
    {
        if (clients[i] && clients[i].connected() && clients[i].available())
        {
            dtp = new (m_dtp_beg) shs::DTP(&clients[i], IP[3]);
            dtp->attach(api);
            dtp->checkBus(&lens[i]);
        }
    }
}

uint8_t shs::TcpServer::sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to,
                                   const shs::settings::shs_ID_t api_ID)
{
    for (uint8_t i = 0; i < maxClients; i++)
    {
        if (clients[i].remoteIP()[3] == to)
        {
            dtp->packDTP(bc, to, api_ID, static_cast<shs::settings::shs_ModuleID_t>(IP[3]));
            clients[i].write(bc->buf, bc->buf[0]);
            return 0;
        }
    }
    return 1;
}

uint8_t shs::TcpServer::sendRAW(uint8_t *buf, const uint8_t size, const shs::settings::shs_ModuleID_t to)
{
    for (uint8_t i = 0; i < maxClients; i++)
    {
        if (clients[i].remoteIP()[3] == to)
        {
            clients[i].write(buf, size);
            return 0;
        }
    }
    return 1;
}
