#pragma once

#include "SHSErrorsHandler.h"
#include "SHSProcess.h"
#include "SHSByteCollector.h"
#include "SHSSensorsKeeper.h"
#include "SHSLoadKeeper.h"
#include "SHSconfig.h"
#include <GyverNTP.h>

namespace shs
{
    typedef void (*sendPacket_t)(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID);
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

    Module();
};
