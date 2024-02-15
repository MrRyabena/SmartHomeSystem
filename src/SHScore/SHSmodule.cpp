#include "SHSmodule.h"

shs::Module shs::module = Module();

shs::Module::Module() {}

shs::Module::~Module()
{
    if (m_processes)
        delete m_processes;
}

void shs::Module::attachProcesses(shs::Process *ptr)
{
    m_processes = ptr;
}

void shs::Module::detachProcesses(bool stopProcesses)
{
    if (stopProcesses)
        m_processes->stop();
    m_processes = nullptr;
}
