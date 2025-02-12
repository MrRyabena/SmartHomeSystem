#pragma once

/*
  A temporary implementation of fixed-point numbers for convenience
*/

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/

#include <stdint.h>
#include <cmath>

#include "shs_types.h"

namespace shs
{
    class SimpleFixed;
}


class shs::SimpleFixed
{
public:
    static constexpr auto DEFAULT_POWER_OF_TEN = 4;

    SimpleFixed(const double value = 0, const uint8_t power_of_ten = DEFAULT_POWER_OF_TEN) noexcept
        : m_value((static_cast<int64_t>(value* std::pow(10, power_of_ten)) << 4) & 0xfffffffffffffff0 | power_of_ten & 0x0f)
    {}

    SimpleFixed& operator=(const int64_t value) { set(value); return *this; }
    SimpleFixed& operator=(const int32_t value) { set(static_cast<int64_t>(value)); return *this; }
    SimpleFixed& operator=(const float value) { set(value); return *this; }
    SimpleFixed& operator=(const double value) { set(value); return *this; }

    void set(const int64_t value, const uint8_t power_of_ten = 0) { m_value = (value << 4) | (power_of_ten ? power_of_ten : getResolution()) & 0x0f; }
    void set(const float   value, const uint8_t power_of_ten = 0) { m_value = (static_cast<int64_t>(value * std::pow(10, power_of_ten ? power_of_ten : getResolution())) << 4) & 0xfffffffffffffff0 | (power_of_ten ? power_of_ten : getResolution()) & 0x0f; }
    void set(const double  value, const uint8_t power_of_ten = 0) { m_value = (static_cast<int64_t>(value * std::pow(10, power_of_ten ? power_of_ten : getResolution())) << 4) & 0xfffffffffffffff0 | (power_of_ten ? power_of_ten : getResolution()) & 0x0f; }

    int64_t getRAW() const { return m_value; }
    int64_t getRAWvalue() const { return m_value >> 4; }
    uint8_t getResolution() const { return m_value & 0x0f; }
    void setResolution(const uint8_t power_of_ten) { set(toDouble(), power_of_ten); }

    float toFloat()   const { return static_cast<float>(getRAWvalue()) / std::pow(10, getResolution()); }
    double toDouble() const { return static_cast<double>(getRAWvalue()) / std::pow(10, getResolution()); }
    int64_t toInt() const { return (getRAWvalue()) / std::pow(10, getResolution()); }

    operator float()    const { return toFloat(); }
    operator double()   const { return toDouble(); }
    operator int64_t()  const { return static_cast<int64_t>(toInt()); }
    operator int32_t()  const { return static_cast<int32_t>(toInt()); }
    operator int16_t()  const { return static_cast<int16_t>(toInt()); }
    operator int8_t()   const { return static_cast<int8_t>(toInt()); }
    operator uint64_t() const { return static_cast<uint64_t>(toInt()); }
    operator uint32_t()  const { return static_cast<uint32_t>(toInt()); }
    operator uint16_t() const { return static_cast<uint16_t>(toInt()); }
    operator uint8_t()  const { return static_cast<uint8_t>(toInt()); }

private:
    int64_t m_value;
};
