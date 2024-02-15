#pragma once
#include "SHSconnectWiFi.h"
#include "SHSTcpClient.h"

namespace shs
{
    class Process;
    class AutoProcesses;
};

class shs::Process
{
public:
    void begin();
    void tick();
    void stop();
};

class shs::AutoProcesses : public shs::Process
{
public:
    shs::TcpClient *tcp;
    shs::DTP *dtp;

    Processes();
    ~Processes();

    void begin();
    void tick();

private:
//shs::Process *m_processes{};
};