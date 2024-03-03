#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
*/

/*
  A mandatory component of the system responsible for the content of the basic elements.
*/

#include "SHSsettings_private.h"
#include "SHSErrorsHandler.h"
#include "SHSProcess.h"
#include "SHSProcessesKeeper.h"
#include "SHSByteCollector.h"
#include "SHSSensorsKeeper.h"
#include "SHSLoadKeeper.h"
#include "SHSconfig.h"
#include <GyverNTP.h>

namespace shs
{
    typedef void (*sendPacket_t)(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t apiID);
    class Module;
    extern Module module;
};

class shs::Module
{
public:
    GyverNTP ntp;
    shs::Config config;
    shs::ErrorsHandler errorsHandler;
    shs::ProcessesKeeper processes;
    shs::SensorsKeeper sensors;
    shs::LoadKeeper load;
    shs::sendPacket_t sendPacket;

    explicit Module();
};
