#pragma once

#include "SHSErrorsHandler.h"
#include "SHSProcess.h"
#include <GyverNTP.h>

namespace shs
{
    namespace settings;

    class Module;
    extern Module module;
};

class shs::Module
{
public:
    GyverNTP ntp(3, 1800);
    shs::Config config;
    shs::ErrorsHandler errorsHandler;
    shs::Process processes;

public:
    explicit Module();
    ~Module();

    inline void begin();
    inline void tick();
    inline void end();
};
