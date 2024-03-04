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
  server.sendPacket(bc, to, api_ID);
}

class APIhandler : public shs::API {
public:
  explicit APIhandler(const shs::settings::shs_ID_t apiID = 0,
                      const shs::settings::shs_ModuleID_t to = 0)
    : ::shs::API(apiID, to) {}


  uint8_t handler(shs::ByteCollector &bc) override {
    shs::DTPpacker parser;
    shs::DTPdata data;

    parser.parseDTP(&bc, data);

    Serial.print("Message form: ");
    Serial.println(data.from);
    Serial.print("Message apiID: ");
    Serial.println(data.apiID);
    Serial.print("Message to: ");
    Serial.println(data.to);
    Serial.println();

    return 0;
  }
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
}
