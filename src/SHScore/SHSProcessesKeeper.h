#pragma once

#include <stdint.h>
#include <vector>
#include "SHSProcess.h"

namespace shs
{
    class ProcessesKeeper;
};

class shs::ProcessesKeeper : public shs::Process
{
public:
    explicit ProcessesKeeper() {};
    void attach(shs::Process *object);
    void detach(shs::Process *object);

    void begin();
    void tick();
    void end();

protected:
    std::vector<shs::Process *> m_ptrs;
    uint8_t m_find(const shs::Process *object);
};
