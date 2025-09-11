#pragma once


#include <shs_types.h>

#include "shs_lib_SensorTypes.h"
#include "shs_settings_private.h"


namespace shs
{
    class SensorAnalog;    // declared in shs_SensorAnalog.h 
    class PhotoSensor;
}


class shs::PhotoSensor : public shs::SensorAnalog
{
public:
    enum class Metrics : uint8_t { RAW, PERCENT, NORMALIZED_255 };
    enum class Status : uint8_t { OK, INPUT_ERROR };

    explicit PhotoSensor(const shs::t::shs_pin_t pin, const uint8_t samples = SENSOR_AVERAGE_SAMPLES);

    void setBounds(uint16_t floor_bound, uint16_t ceil_bound);
    void setFloorBound(const uint16_t floor_bound) { setBounds(floor_bound, m_ceil_bound); }
    void setCeilBound(const uint16_t ceil_bound) { setBounds(m_floor_bound, ceil_bound); }

    uint16_t getFloorBound() const { return m_floor_bound; }
    uint16_t getCeilBound() const { return m_ceil_bound; }

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return m_getValue<int32_t>(metric); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return static_cast<shs::t::shs_fixed_t>(m_getValue<shs::t::shs_float_t>(metric)); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override { return static_cast<shs::t::shs_float_t>(m_getValue<shs::t::shs_float_t>(metric)); }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(m_getValue<shs::t::shs_double_t>(metric)); }


protected:
    uint16_t m_floor_bound{};
    uint16_t m_ceil_bound{};

    template <typename T>
    T m_getValue(const uint8_t metric)
    {
        if (m_metric == Metrics::RAW) return m_value;
        if (m_floor_bound == m_ceil_bound) return {};

        switch (static_cast<Metrics>(metric))
        {
            case Metrics::PERCENT: return map(static_cast<T>(m_value), m_floor_bound, m_ceil_bound, 0, 100); break;
            case Metrics::NORMALIZED_255: return map(static_cast<T>(m_value), m_floor_bound, m_ceil_bound, 0, 255); break;
        }

        return {};
    }
};
