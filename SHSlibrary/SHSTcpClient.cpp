#include "SHSTcpClient.h"

shs::TcpClient::TcpClient(const uint8_t *IPaddress, void (*TCPhandle)(shs::DTPdata &), uint16_t _port)
    : dtp(new shs::DTP(IPaddress[3], (Stream*)&client, TCPhandle))
{
    IP = IPaddress;
    _TCPhandle = TCPhandle;
    port = _port;
}

shs::TcpClient::~TcpClient()
{
    delete dtp;
}

void shs::TcpClient::begin()
{
    client.connect(IP, port);
}

void shs::TcpClient::tick()
{
    if (client && client.connected())
        dtp->checkBus(&len);
}
