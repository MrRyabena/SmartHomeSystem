#include <SHSsettings_private.h>
#include "settings.h"
#include <SHSsettings.h>


#include <SHSModule.h>
#include <SHSAutoProcesses.h>
#include <SHSLoadPWM.h>
#include <SHSByteCollector.h>

shs::AutoProcesses processes;

shs::LoadPWM bulb(shs::settings::bulbID, bulbPIN, &shs::module.processes);


void sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID) {
  processes.dtp.sendPacket(bc, to, api_ID, shs::module.config.ID);
}

void setup() {
  Serial.begin(115200);
  Serial.println("OK 21");
  // For now, manually, then it will be automatic {
  shs::module.sendPacket = sendPacket;
  shs::module.config.ID = shs::settings::SmartLighterID;
  shs::module.config.serverID = shs::settings::ServerID;
  shs::module.config.mode = shs::Mode::on;

  Serial.println("OK 28");

  shs::module.load.attach(&bulb);
  // }
  Serial.println("OK 32");
  processes.begin();
  Serial.println("OK 34");
  if (processes.tcp.connected()) Serial.println("connected!");
  else Serial.println("no connected!");
}

void loop() {

  //processes.dtp.tick();

  static uint32_t tmr{};

  if (millis() - tmr >= 10000) {
    shs::ByteCollector bc(2);
    bc.add(15);
    shs::module.sendPacket(&bc, 4, 4);
    tmr = millis();
    Serial.println("Send!");
  }
  processes.tick();
}
