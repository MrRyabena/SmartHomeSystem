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
    explicit ProcessesKeeper();
    void attach(shs::Process *object);
    void detach(shs::Process *object);

    void begin();
    void tick();
    void end();

private:
    std::vector<shs::Process *> _ptrs;
    uint8_t _fined(shs::Process *object);
};
