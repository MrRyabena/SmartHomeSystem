#pragma once

namespace shs
{
    class Process;
    class AutoProcesses;
};

class shs::Process
{
public:
    virtual void begin();
    virtual void tick();
    virtual void end();
};
