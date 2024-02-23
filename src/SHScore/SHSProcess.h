#pragma once

namespace shs
{
    class Process;
};

class shs::Process
{
public:
    virtual void begin() = 0;
    virtual void tick() = 0;
    virtual void end() = 0;
};
