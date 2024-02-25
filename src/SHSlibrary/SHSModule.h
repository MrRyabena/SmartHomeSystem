#pragma once

#include "../SHScore/SHSErrorsHandler.h"
#include "../SHScore/SHSProcess.h"
#include "../SHScore/SHSSensorsKeeper.h"
#include "../SHScore/SHSLoadKeeper.h"
#include "../SHScore/SHSconfig.h"

#include <GyverNTP.h>

namespace shs
{
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

    Module();
};
