#pragma once

/*
  Last update: v2.3.0
  Versions:
    v2.3.0 — created.
*/

#include "shs_SensorAnalog.h"


namespace shs
{
    class SensorAnalogMapped;
}


class shs::SensorAnalogMapped : public shs::SensorAnalog
{
public:
    enum class Metrics : uint8_t { RAW, PERCENT, NORMALIZED_255 };

    explicit SensorAnalogMapped(shs::t::shs_pin_t pin, uint16_t lower_bound, uint16_t upper_bound, shs::Sensor::Type type = shs::Sensor::ANALOG_MAPPED, uint8_t samples = SENSOR_AVERAGE_SAMPLES);

    void setBounds(uint16_t lower_bound, uint16_t upper_bound);
    void setLowerBound(const uint16_t lower_bound) { setBounds(lower_bound, m_upper_bound); }
    void setUpperBound(const uint16_t upper_bound) { setBounds(m_lower_bound, upper_bound); }

    [[nodiscard]] uint16_t getLowerBound() const { return m_lower_bound; }
    [[nodiscard]] uint16_t getUpperBound() const { return m_upper_bound; }

    template <typename T>
    static T map(const T value, const T from_low, const T from_high, const T to_low, const T to_high);

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override;
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override;
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override;
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override;

protected:
    uint16_t m_lower_bound;
    uint16_t m_upper_bound;
};

template<typename T>
inline T shs::SensorAnalogMapped::map(const T value, const T from_low, const T from_high, const T to_low, const T to_high)
{
    if (from_high == from_low) return to_low;                 // Prevent division by zero, return the lowest value of the target range.
    if (value <= from_low) return to_low;                     // If the value is below the source range, return the lowest value of the target range.
    if (value >= from_high) return to_high;                   // If the value is above the source range, return the highest value of the target range.

    return static_cast<T>((value - from_low) * (to_high - to_low) / (from_high - from_low) + to_low);  // Map the value from the source range to the target range.
}
