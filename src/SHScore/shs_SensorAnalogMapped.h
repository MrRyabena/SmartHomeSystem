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


/**
 * @brief Analog sensor wrapper that maps raw readings into alternate metric ranges.
 */
class shs::SensorAnalogMapped : public shs::SensorAnalog
{
public:
    /**
     * @brief Supported output mappings for the analog sensor value.
     */
    enum class Metrics : uint8_t { RAW, PERCENT, NORMALIZED_255 };

    /**
     * @brief Creates a mapped analog sensor with the given bounds.
     */
    explicit SensorAnalogMapped(shs::t::shs_pin_t pin, uint16_t lower_bound, uint16_t upper_bound, shs::Sensor::Type type = shs::Sensor::ANALOG_MAPPED, uint8_t samples = SENSOR_AVERAGE_SAMPLES);

    /**
     * @brief Updates the source range used for metric mapping.
     */
    void setBounds(uint16_t lower_bound, uint16_t upper_bound);

    /**
     * @brief Updates only the lower bound of the source range.
     */
    void setLowerBound(const uint16_t lower_bound) { setBounds(lower_bound, m_upper_bound); }

    /**
     * @brief Updates only the upper bound of the source range.
     */
    void setUpperBound(const uint16_t upper_bound) { setBounds(m_lower_bound, upper_bound); }

    /**
     * @brief Returns the lower source bound.
     */
    [[nodiscard]] uint16_t getLowerBound() const { return m_lower_bound; }

    /**
     * @brief Returns the upper source bound.
     */
    [[nodiscard]] uint16_t getUpperBound() const { return m_upper_bound; }

    /**
     * @brief Maps a value from one range into another.
     */
    template <typename T>
    static T map(const T value, const T from_low, const T from_high, const T to_low, const T to_high);

    /**
     * @brief Returns the mapped value as a signed integer.
     */
    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override;

    /**
     * @brief Returns the mapped value as a fixed-point number.
     */
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override;

    /**
     * @brief Returns the mapped value as a float.
     */
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override;

    /**
     * @brief Returns the mapped value as a double.
     */
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override;

protected:
    /**
     * @brief Lower bound of the input range.
     */
    uint16_t m_lower_bound;

    /**
     * @brief Upper bound of the input range.
     */
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
