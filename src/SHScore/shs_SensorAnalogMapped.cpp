#include "shs_SensorAnalogMapped.h"


shs::SensorAnalogMapped::SensorAnalogMapped(const shs::t::shs_pin_t pin,
    const uint16_t lower_bound, const uint16_t upper_bound,
    const shs::Sensor::Type type, const uint8_t samples)
    : SensorAnalog(pin, samples, type), m_lower_bound(lower_bound), m_upper_bound(upper_bound)
{}


void shs::SensorAnalogMapped::setBounds(const uint16_t lower_bound, const uint16_t upper_bound)
{
    m_lower_bound = lower_bound;
    m_upper_bound = upper_bound;
}


int32_t shs::SensorAnalogMapped::getValueI(const uint8_t metric)
{
    switch (static_cast<Metrics>(metric))
    {
        case Metrics::RAW: return static_cast<int32_t>(m_value);
        case Metrics::PERCENT: return map<int32_t>(m_value, m_lower_bound, m_upper_bound, 0, 100);
        case Metrics::NORMALIZED_255: return map<int32_t>(m_value, m_lower_bound, m_upper_bound, 0, 255);
    }
    return 0;
}


shs::t::shs_fixed_t shs::SensorAnalogMapped::getValueFx(const uint8_t metric)
{
    return static_cast<shs::t::shs_fixed_t>(getValueF(metric));
}


shs::t::shs_float_t shs::SensorAnalogMapped::getValueF(const uint8_t metric)
{
    switch (static_cast<Metrics>(metric))
    {
        case Metrics::RAW: return m_value;
        case Metrics::PERCENT: return map<shs::t::shs_float_t>(m_value, m_lower_bound, m_upper_bound, 0, 100);
        case Metrics::NORMALIZED_255: return map<shs::t::shs_float_t>(m_value, m_lower_bound, m_upper_bound, 0, 255);
    }
    return 0;
}


shs::t::shs_double_t shs::SensorAnalogMapped::getValueD(const uint8_t metric)
{
    switch (static_cast<Metrics>(metric))
    {
        case Metrics::RAW: return static_cast<shs::t::shs_double_t>(m_value);
        case Metrics::PERCENT: return map<shs::t::shs_double_t>(m_value, m_lower_bound, m_upper_bound, 0, 100);
        case Metrics::NORMALIZED_255: return map<shs::t::shs_double_t>(m_value, m_lower_bound, m_upper_bound, 0, 255);
    }
    return 0;
}
