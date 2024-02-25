#pragma once

#ifdef ESP8266
#include <Arduino.h>


#include <ESP8266WiFi.h>




#include "..\SHScore\SHSProcess.h"
#include "..\SHScore\SHSTcpClient.h"
#include "..\SHScore\SHSdtp.h"
#include "..\SHScore\SHSProcessesKeeper.h"
#include "..\SHScore\SHSconnectWiFi.h"
#include "SHSModule.h"
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
    shs::ProcessesKeeper keeper;

    explicit AutoProcesses();
    ~AutoProcesses();

    void begin() override;
    void tick() override;
    void end() override;
};
#endif
