#define _Arduino_
#include <SHSsettings_private.h>
#include <SHSTcpServer.h>
#include <SHSLoadAPI.h>
#include <SHSModule.h>
#include <SHSconnectWiFi.h>

#include <SHSByteCollector.h>
#include <SHSdtp.h>
#include <SHSAPI.h>

shs::TcpServer server(shs::settings::COM_IP);

void sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID) {
  uint8_t value{};
  value = server.sendPacket(bc, to, api_ID);
  Serial.println(value);
}

class APIhandler : public shs::API {
public:
  explicit APIhandler(const shs::settings::shs_ID_t apiID = 0,
                      const shs::settings::shs_ModuleID_t to = 0)
    : ::shs::API(apiID, to) {}


  uint8_t handler(shs::ByteCollector &bc) override;
};


void setup() {
  Serial.begin(115200);
  shs::module.sendPacket = sendPacket;
  shs::module.config.ID = 4;
  shs::module.config.serverID = 4;
  shs::module.config.mode = shs::Mode::on;

  Serial.println("47");
  //shs::setMac(shs::module.config.ID);
  Serial.println("49");
  shs::connectWiFi();
  Serial.println("50");

  shs::module.sensors.setup();
  shs::module.load.setup();
  Serial.println("54");

  server.api = new APIhandler;
  Serial.println("57");

  server.begin();
  Serial.println("ok");
}

void loop() {
  //shs::module.ntp.tick();
  server.tick();

  static uint32_t tmr{};

  if (millis() - tmr >= 10000) {
    shs::ByteCollector bc(3);
    bc.add(shs::settings::thermID, 2);
    bc.add(0, 1);
    //sendPacket(&bc, shs::settings::SmartThermID, 10);
    sendPacket(&bc, shs::settings::appID, shs::settings::Sensor_apiID);
    tmr = millis();
  }
}
