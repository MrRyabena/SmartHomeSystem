#pragma once

#include "SHSErrorsHandler.h"
#include "SHSProcesses.h"
#include <GyverNTP.h>

namespace shs
{
    namespace settings;

    class Module;
    extern Module module;

    struct Config;

    enum Mode;

};

struct shs::Config
{
    uint8_t ID{};
    uint8_t serverID{};
    shs::Mode mode{};
};

enum shs::Mode : uint8_t
{
    off,
    standby,
    sleep,
};

class shs::Module
{
public:
    GyverNTP ntp(3, 1800);
    shs::Config config;
    shs::ErrorsHandler errorsHandler;

public:
    explicit Module();
    ~Module();

    void attachProcesses(shs::Process *ptr);
    void detachProcesses(bool stopProcesses = true);

private:
    shs::Process *m_processes{};
};
