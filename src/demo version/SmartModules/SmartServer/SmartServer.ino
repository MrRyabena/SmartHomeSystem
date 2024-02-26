#define _Arduino_
#include <SHSsettings_private.h>
#include <SHSTcpServer.h>
#include <SHSLoadAPI.h>
#include <SHSModule.h>
#include <SHSconnectWiFi.h>



shs::TcpServer server(shs::settings::COM_IP);

void sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID) {
  server.sendPacket(bc, to, api_ID);
}



void setup() {
  shs::module.sendPacket = sendPacket;
  shs::module.config.ID = 4;
  shs::module.config.serverID = 4;
  shs::module.config.mode = shs::Mode::on;

  shs::setMac(shs::module.config.ID);
  shs::connectWiFi();

  shs::module.sensors.setup();
  shs::module.load.setup();

  server.begin();
}

void loop() {
  shs::module.ntp.tick();
  server.tick();
}
