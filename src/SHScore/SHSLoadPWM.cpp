#include "SHSLoadPWM.h"

shs::LoadPWM::LoadPWM(shs::settings::shs_ID_t ID, uint8_t pin,
                      shs::ProcessesKeeper *keeper, shs::LoadType::LoadType ltype)
    : ::shs::Load(ID, ltype), m_pin(pin), m_keeper(keeper) {}

shs::LoadPWM::~LoadPWM()
{
    if (m_keeper)
        m_keeper->detach(this);
    if (m_stc)
        delete m_stc;
}

inline void shs::LoadPWM::setup() { pinMode(m_pin, OUTPUT); }

inline void shs::LoadPWM::setKeeper(shs::ProcessesKeeper *keeper) { m_keeper = keeper; }

void shs::LoadPWM::on(uint8_t value, uint8_t smoothing, const shs::settings::shs_ID_t ID)
{
    if (smoothing)
    {
        m_keeper->attach(this);
        return;
    }

    analogWrite(m_pin, value);
}

void shs::LoadPWM::on(uint16_t value, uint16_t smoothing, const shs::settings::shs_ID_t ID)
{
    if (smoothing)
    {
        m_keeper->attach(this);
        m_stc = new Smoothing;
        m_stc->targetValue = value;
        m_stc->k_smoothing = smoothing;
        return;
    }

    analogWrite(m_pin, value);
}

inline void shs::LoadPWM::off(uint16_t smoothing, const shs::settings::shs_ID_t ID) { on(0, smoothing); }

inline void shs::LoadPWM::begin() { setup(); }

void shs::LoadPWM::tick()
{
    if (millis() - m_stc->tmr < m_stc->k_smoothing)
        return;

    if (!m_stc)
    {
        m_keeper->detach(this);
        return;
    }

    if (++m_stc->value >= m_stc->targetValue)
    {
        delete m_stc;
        m_stc = nullptr;

        m_keeper->detach(this);
    }
    analogWrite(m_pin, m_stc->value);
}

void shs::LoadPWM::end() {}
