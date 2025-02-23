#include "shs_lib_Thermistor.h"

void shs::Thermistor::update()
{
    uint32_t average{};
    for (uint16_t i = 0; i < m_samples; i++) average += analogRead(m_pin);
    auto value = computeTemperature(shs::t::shs_float_t(average) / m_samples, m_RES_R, m_TH_B, m_TH_TEMP, m_TH_R, m_ADC_RESOLUTION);
    if (!std::is_nan(value)) m_value = value;
}

void shs::Thermistor::updateFast()
{
    auto value = computeTemperature(analogRead(m_pin), m_RES_R, m_TH_B, m_TH_TEMP, m_TH_R, m_ADC_RESOLUTION);
    if (!std::is_nan(value)) m_value = value;
}

uint8_t shs::Thermistor::getStatus()
{
    auto signal = analogRead(m_pin);
    if (signal <= 0 || signal >= (1 << m_ADC_RESOLUTION) - 4) return static_cast<uint8_t>(Status::INPUT_OVERSHOOTING);
    return static_cast<uint8_t>(Status::OK);
}


shs::t::shs_float_t shs::Thermistor::computeTemperature(const shs::t::shs_float_t signal, const uint32_t res_R, const uint16_t th_B, const uint8_t th_Temp, const uint32_t th_R, const uint8_t ADC_resolution)
{
    if (signal <= 0 || isnan(signal)) return INFINITY;

    // Calculate the resistance of the thermistor
    shs::t::shs_float_t value = res_R / (static_cast<shs::t::shs_float_t>((1 << ADC_resolution) - 1) / signal - 1.0f);

    // Calculate the temperature in 1/Kelvin
    value = (std::log(value / th_R) / th_B) + (1.0 / (th_Temp - ABSOLUTE_ZERO));

    // Convert to Celsius
    return (1.0 / value) + ABSOLUTE_ZERO;
}
