#include "SHSTcpServer.h"

shs::TcpServer::TcpServer(const uint8_t *IPaddress, void (*TCPhandle)(shs::DTPdata &), uint16_t port, uint8_t max_clients)
    : server(new WiFiServer(port)),
      clients(new WiFiClient[max_clients]{}),
      lens(new uint8_t[max_clients]{}),
      dtp(new shs::DTP(IPaddress[3], (Stream*)server, TCPhandle))

{
    IP = IPaddress;
    maxClients = max_clients;
    _TCPhandle = TCPhandle;
}

shs::TcpServer::~TcpServer()
{
    delete server;
    delete[] clients;
    delete[] lens;
    delete dtp;
}

void shs::TcpServer::begin()
{
    server->begin();
    server->setNoDelay(true);
}

void shs::TcpServer::tick()
{

    if (server->hasClient())
    {
        for (i = 0; i < maxClients; i++)
        {
            if (!clients[i] || (clients[i] && !clients[i].connected()))
            {

                if (clients[i])
                    clients[i].stop();
                clients[i] = server->available();
                break;
            }
        }
        WiFiClient client = server->available();
        client.stop();
    }

    for (i = 0; i < maxClients; i++)
    {
        if (clients[i] && clients[i].connected())
            dtp->checkBus(&lens[i]);
    }
}

uint8_t shs::TcpServer::sendPacket(shs::ByteCollector *col, uint8_t id)
{
    for (uint8_t i = 0; i < maxClients; i++)
    {
        if (clients[i].remoteIP()[3] == id)
        {
            dtp->packDTP(col, id);
            clients[i].write(col->buf, col->buf[0]);
            return 0;
        }
    }
    return 1;
}
