#include "SHSAutoRun.h"

shs::AutoRun::AutoRun()
    : tcp(new shs::TcpClient()), dtp(new shs::DTP(tcp))
{
}

shs::AutoRun::~AutoRun()
{
    if (dtp)
        delete dtp;
    if (tcp)
        delete tcp;
}

void shs::AutoRun::begin()
{
    shs::setMac(shs::module.config.ID);
    shs::connectWiFi();

    tcp->connect(shs::module.config.serverID, shs::settings::TCP_PORT);
}

void shs::AutoRun::tick()
{
    dtp->tick();
    shs::module.ntp.tick();
}
