#include "SHSCallbacksKeeper.h"

/*
  ----------------------------------------
  PUBLIC
  ----------------------------------------
*/

void shs::CallbacksKeeper::attach(shs::API *object)
{
    if (m_find(object) == 0xff)
        m_ptrs.push_back(object);
    m_ptrs.shrink_to_fit();
}

void shs::CallbacksKeeper::detach(shs::API *object)
{
    uint8_t ind = m_find(object);

    if (ind == 0xff)
        return;
    for (uint8_t i = ind; i < m_ptrs.size() - 1; i++)
        m_ptrs[i] = m_ptrs[i + 1];
    m_ptrs.pop_back();
    m_ptrs.shrink_to_fit();
}

uint8_t shs::CallbacksKeeper::handler(shs::ByteCollector &data)
{
    uint8_t status = 0;
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i])
            status = m_ptrs[i]->handler(data);

    return status;
}

/*
  ----------------------------------------
  PRIVATE/PROTECTED
  ----------------------------------------
*/

uint8_t shs::CallbacksKeeper::m_find(shs::API *object)
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i] == object)
            return i;
    return 0xff;
}
