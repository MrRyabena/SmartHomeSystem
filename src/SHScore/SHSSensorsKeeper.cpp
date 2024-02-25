#include "SHSSensorsKeeper.h"

void shs::SensorsKeeper::attach(shs::Sensor *object)
{
    if (m_find(object) != 0xff)
        return;
    m_ptrs.push_back(object);
    m_ptrs.shrink_to_fit();
}

void shs::SensorsKeeper::detach(shs::Sensor *object)
{
    uint8_t ind = m_find(object);
    if (ind == 0xff)
        return;

    for (uint8_t i = ind; i < m_ptrs.size() - 1; i++)
        m_ptrs[i] = m_ptrs[i + 1];
    m_ptrs.pop_back();
    m_ptrs.shrink_to_fit();
}

void shs::SensorsKeeper::setup()
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i])
            m_ptrs[i]->setup();
}

int16_t shs::SensorsKeeper::getValueI(const shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return INT16_MAX;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return INT16_MAX;

    return m_ptrs[ind]->getValueI();
}

shs::settings::shs_float_t shs::SensorsKeeper::getValueF(shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return 0.0;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return 0.0;

    return m_ptrs[ind]->getValueF();
}

shs::settings::shs_double_t shs::SensorsKeeper::getValueD(shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return 0.0;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return 0.0;

    return m_ptrs[ind]->getValueD();
}

int16_t shs::SensorsKeeper::getAverageI(shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return INT16_MAX;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return INT16_MAX;

    return m_ptrs[ind]->getAverageI();
}

shs::settings::shs_float_t shs::SensorsKeeper::getAverageF(shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return 0.0;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return 0.0;

    return m_ptrs[ind]->getAverageF();
}

shs::settings::shs_double_t shs::SensorsKeeper::getAverageD(shs::settings::shs_ID_t ID)
{
    if (ID == 0)
        return 0.0;
    uint8_t ind = find(ID);
    if (ind == 0xff)
        return 0.0;

    return m_ptrs[ind]->getAverageD();
}

uint8_t shs::SensorsKeeper::find(const shs::settings::shs_ID_t ID)
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if ((m_ptrs[i]) && m_ptrs[i]->getID() == ID)
            return i;
    return 0xff;
}

uint8_t shs::SensorsKeeper::m_find(const shs::Sensor *object)
{
    for (uint8_t i = 0; i < m_ptrs.size(); i++)
        if (m_ptrs[i] == object)
            return i;
    return 0xff;
}