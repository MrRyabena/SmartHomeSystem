#include "SHSLoadKeeper.h"

void shs::LoadKeeper::attach(shs::Load *object)
{
    if (m_find(object) != 0xff)
        return;
    m_ptrs.push_back(object);
    m_ptrs.shrink_to_fit();
}

void shs::LoadKeeper::detach(shs::Load *object)
{
    uint8_t ind = m_find(object);
    if (ind == 0xff)
        return;

    for (uint8_t i = ind; i < m_ptrs.size() - 1; i++)
        m_ptrs[i] = m_ptrs[i + 1];
    m_ptrs.pop_back();
    m_ptrs.shrink_to_fit();
}

void shs::LoadKeeper::setup()
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i])
            m_ptrs[i]->setup();
}

void shs::LoadKeeper::on(const uint8_t value, const uint8_t smoothing, const shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return;

    m_ptrs[ind]->on(value, smoothing);
}

void shs::LoadKeeper::on(const uint16_t value, const uint16_t smoothing, const shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return;

    m_ptrs[ind]->on(value, smoothing);
}

void shs::LoadKeeper::off(const uint16_t smoothing, const shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return;

    m_ptrs[ind]->off(smoothing);
}

uint8_t shs::LoadKeeper::find(const shs::settings::shs_ID_t ID)
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if ((m_ptrs[i]) && m_ptrs[i]->getID() == ID)
            return i;
    return 0xff;
}

/*
  ----------------------------------------
  PRIVATE/PROTECTED
  ----------------------------------------
*/

uint8_t shs::LoadKeeper::m_find(const shs::Load *object)
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i] == object)
            return i;
    return 0xff;
}
