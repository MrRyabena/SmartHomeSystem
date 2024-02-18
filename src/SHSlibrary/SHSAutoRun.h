#pragma once
#include "..\SHScore\SHSProcess.h"
#include "..\SHScore\SHSTcpClient.h"
#include "..\SHScore\SHSdtp.h"

namespace shs
{
    class AutoRun;
}

class shs::AutoRun : public shs::Process
{
public:
    shs::TcpClient *tcp;
    shs::DTP *dtp;

    AutoRun();
    ~AutoRun();

    void begin();
    void tick();

private:
    // shs::Process *m_processes{};
};