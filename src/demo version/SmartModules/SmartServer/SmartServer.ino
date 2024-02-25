
#include <SHSsettings_private.h>
#include <SHSTcpServer.h>
#include <SHSModule.h>
#include <SHSconnectWiFi.h>

shs::TcpServer server(shs::settings::COM_IP);

void setup() {
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
