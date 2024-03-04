#include <SHSsettings_private.h>
#include "settings.h"
#include <SHSsettings.h>

#include <SHSModule.h>
#include <SHSAutoProcesses.h>

#include <SHSLoadSwitch.h>
#include <SHSSensorAnalog.h>

shs::AutoProcesses processes;
shs::LoadSwitch ledBulb(shs::settings::ledBulbID, ledBulbPIN);

shs::SensorAnalog photo(shs::settings::photoID);

void sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t apiID) {
  processes.dtp.sendPacket(bc, to, apiID, shs::module.config.ID);
}

void setup() {
  // For now, manually, then it will be automatic {
  shs::module.sendPacket = sendPacket;
  shs::module.config.ID = shs::settings::SmartBulbID;
  shs::module.config.serverID = shs::settings::ServerID;
  shs::module.config.mode = shs::Mode::on;

  shs::module.load.attach(&ledBulb);
  shs::module.sensors.attach(&photo);
  // }

  processes.begin();
}

void loop() {
  processes.tick();
}
