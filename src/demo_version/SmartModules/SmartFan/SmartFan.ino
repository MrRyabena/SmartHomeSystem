#include <SHSsettings_private.h>
#include "settings.h"

#include <SHSModule.h>
#include <SHSAutoProcesses.h>

#include <SHSLoadPWM.h>
#include <SHSSensorAnalog.h>


shs::AutoProcesses processes;

shs::LoadPWM bulbH(bulbH_ID, bulbH_pin, &shs::module.processes);
shs::SensorAnalog therm(thermID);

void sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID) {
  processes.dtp.sendPacket(bc, to, api_ID, shs::module.config.ID);
}

void setup() {
  // For now, manually, then it will be automatic {
  shs::module.sendPacket = sendPacket;
  shs::module.config.ID = SmartFanID;
  shs::module.config.serverID = ServerID;
  shs::module.config.mode = shs::Mode::on;

  shs::module.load.attach(&bulbH);
  shs::module.sensors.attach(&therm);
  // }

  processes.begin();
}

void loop() {
  processes.tick();
}
