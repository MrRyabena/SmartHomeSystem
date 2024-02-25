#include "SHSAutoProcesses.h"
#ifdef ESP8266
shs::AutoProcesses::AutoProcesses()
    : dtp(&tcp, module.config.ID) {}

void shs::AutoProcesses::begin()
{
    shs::setMac(shs::module.config.ID);
    shs::connectWiFi();

    tcp.connect(shs::module.config.serverID, 5000);

    shs::module.sensors.setup();
    shs::module.load.setup();
}

void shs::AutoProcesses::tick()
{
    dtp.tick();
    shs::module.ntp.tick();
}

void shs::AutoProcesses::end()
{
}
#endif
