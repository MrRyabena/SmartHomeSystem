#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  Quick Configurator for ESP8266
*/

#ifdef ESP8266
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "..\SHScore\SHSProcess.h"
#include "..\SHScore\SHSdtp.h"
#include "..\SHScore\SHSProcessesKeeper.h"
#include "..\SHScore\SHSconnectWiFi.h"
#include "..\SHScore\SHSModule.h"
#include "..\SHScore\SHSLoadAPI.h"
#include "..\SHScore\SHSSensorAPI.h"

// #ifndef _SHS_SETTINGS_
// #include <SHSsettings.h>
// #endif

namespace shs
{
    class AutoProcesses;
}

class shs::AutoProcesses : public shs::Process
{
public:
    WiFiClient tcp;
    shs::DTP dtp;
    shs::LoadAPIhandler loadAPI;
    shs::SensorAPIhandler sensorsAPI;

    explicit AutoProcesses();
    //~AutoProcesses();

    void begin() override;
    void tick() override;
    void end() override;
};

shs::AutoProcesses::AutoProcesses()
    : dtp(&tcp, module.config.ID),
      sensorsAPI(shs::settings::Sensor_apiID, shs::settings::SERVER_ID, &shs::module.sensors),
      loadAPI(shs::settings::Load_apiID, shs::settings::SERVER_ID, &shs::module.load) {}

void shs::AutoProcesses::begin()
{
    shs::setMac(shs::module.config.ID);
    shs::connectWiFi();
    uint8_t ip[4];
    ip[0] = shs::settings::COM_IP[0];
    ip[1] = shs::settings::COM_IP[1];
    ip[2] = shs::settings::COM_IP[2];
    ip[3] = shs::module.config.serverID;
    tcp.connect(ip, 50000);
    tcp.setNoDelay(true);

    dtp.attach(&loadAPI);
    dtp.attach(&sensorsAPI);

    shs::module.sensors.setup();
    shs::module.load.setup();
    shs::module.processes.begin();
}

void shs::AutoProcesses::tick()
{
    dtp.tick();
    shs::module.ntp.tick();
    shs::module.processes.tick();
}

void shs::AutoProcesses::end()
{
    shs::module.processes.end();
}

#endif
