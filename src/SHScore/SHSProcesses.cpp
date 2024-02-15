#include "SHSProcesses.h"

shs::AutoProcesses::AutoProcesses()
    : tcp(new shs::TcpClient()), dtp(new shs::DTP(tcp, handler))
{
}

shs::AutoProcesses::~AutoProcesses()
{
    if (dtp)
        delete dtp;
    if (tcp)
        delete tcp;
}

void shs::AutoProcesses::begin()
{
    shs::setMac(shs::module.config.ID);
    shs::connectWiFi();

    tcp->connect(shs::module.config.serverID, shs::settings::TCP_PORT);
}

void shs::AutoProcesses::tick()
{
    dtp->tick();
    shs::module.ntp.tick();
}
