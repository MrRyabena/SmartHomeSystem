#include "SHSProcessesKeeper.h"

void shs::ProcessesKeeper::attach(shs::Process *object)
{
    if (m_find(object) == 0xff)
        m_ptrs.push_back(object);
    m_ptrs.shrink_to_fit();
}

void shs::ProcessesKeeper::detach(shs::Process *object)
{
    uint8_t ind = m_find(object);
    if (ind == 0xff)
        return;
    for (uint8_t i = ind; i < m_ptrs.size() - 1; i++)
        m_ptrs[i] = m_ptrs[i + 1];
    m_ptrs.pop_back();
    m_ptrs.shrink_to_fit();
}

void shs::ProcessesKeeper::begin()
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i])
            m_ptrs[i]->begin();
}

void shs::ProcessesKeeper::tick()
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i])
            m_ptrs[i]->tick();
}

void shs::ProcessesKeeper::end()
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i])
            m_ptrs[i]->end();
}

/*
  ----------------------------------------
  PRIVATE/PROTECTED
  ----------------------------------------
*/

uint8_t shs::ProcessesKeeper::m_find(const shs::Process *object)
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i] == object)
            return i;
    return 0xff;
}
