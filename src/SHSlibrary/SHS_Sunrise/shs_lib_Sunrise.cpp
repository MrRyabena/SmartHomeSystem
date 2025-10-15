#include "shs_lib_Sunrise.h"

void shs::Sunrise::sunrise(const shs::t::shs_time_t time)
{
    m_timer.setTimeout(time / 256);
    m_iteration = 0;
    m_incr = 1;
    
    m_on_loads(m_iteration);
    m_iteration += m_incr;
}

void shs::Sunrise::sundown(const shs::t::shs_time_t time)
{
    m_timer.setTimeout(time / 256);
    m_timer.reset();
    m_iteration = 255;
    m_incr = -1;
    
    m_on_loads(m_iteration);
    m_iteration += m_incr;
}

void shs::Sunrise::tick()
{
    if (m_iteration <= 255 && m_timer.check())
    {
        m_on_loads(m_iteration);
        m_iteration += m_incr;        
    }
}

void shs::Sunrise::m_on_loads(uint16_t value)
{
    for (auto& load : m_loads) load->on(value);
}
