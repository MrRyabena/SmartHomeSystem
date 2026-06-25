#pragma once

#include <shs_types.h>
#include <shs_lib_SensorTypes.h>

namespace shs
{
    class SensorAnalog;    // declared in shs_SensorAnalog.h
    namespace lib
    {
        class SoilMoistureSensor;
    }
}


class shs::lib::SoilMoistureSensor : public shs::SensorAnalog
{
public:
    enum class Metrics : uint8_t { RAW, PERCENT, NORMALIZED_255 };
    enum class Status : uint8_t { OK, INPUT_ERROR };

    explicit SoilMoistureSensor(shs::t::shs_pin_t pin, uint8_t samples = SENSOR_AVERAGE_SAMPLES);
    explicit SoilMoistureSensor(shs::t::shs_pin_t pin, uint16_t lower_bound, uint16_t upper_bound, uint8_t samples = SENSOR_AVERAGE_SAMPLES);

    void setBounds(uint16_t lower_bound, uint16_t upper_bound);
    void setLowerBound(const uint16_t lower_bound) { setBounds(lower_bound, m_upper_bound); }
    void setUpperBound(const uint16_t upper_bound) { setBounds(m_lower_bound, upper_bound); }

    [[nodiscard]] uint16_t getLowerBound() const { return m_lower_bound; }
    [[nodiscard]] uint16_t getUpperBound() const { return m_upper_bound; }

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return m_getValue<int32_t>(metric); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return static_cast<shs::t::shs_fixed_t>(m_getValue<shs::t::shs_float_t>(metric)); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override { return static_cast<shs::t::shs_float_t>(m_getValue<shs::t::shs_float_t>(metric)); }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(m_getValue<shs::t::shs_double_t>(metric)); }

protected:
    uint16_t m_lower_bound{};
    uint16_t m_upper_bound{};

    template <typename T>
    T m_getValue(const uint8_t metric) const
    {
        if (m_metric == Metrics::RAW) return m_value;
        if (m_lower_bound == m_upper_bound) return {};

        switch (static_cast<Metrics>(metric))
        {
            case Metrics::PERCENT: return map(static_cast<T>(m_value), m_lower_bound, m_upper_bound, 0, 100); break;
            case Metrics::NORMALIZED_255: return map(static_cast<T>(m_value), m_lower_bound, m_upper_bound, 0, 255); break;
        }

        return {};
    }
};
