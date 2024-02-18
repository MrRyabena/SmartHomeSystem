#include "SHSModule.h"

shs::Module shs::module = Module();

shs::Module::Module() {}

shs::Module::~Module()
{
    if (m_processes)
        delete m_processes;
}

void shs::Module::begin()
{
    processes.begin();
}

void shs::Module::tick()
{
    ntp.tick();
    processes.tick();
}

void shs::Module::end()
{
    processes.end();
}
