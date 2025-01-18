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
        : m_value(static_cast<int32_t>(value* std::pow(10, power_of_ten)) & 0xffffffe0 | power_of_ten & 0x1f)
    {}

    float toFloat()   const { return static_cast<float>(m_value & 0xffffffe0) * (m_value & 0x1f); }
    double toDouble() const { return static_cast<double>(m_value & 0xffffffe0) * (m_value & 0x1f); }

    void set(const int32_t value, const uint8_t power_of_ten = DEFAULT_POWER_OF_TEN) { m_value = value << 5; }
    void set(const float   value, const uint8_t power_of_ten = DEFAULT_POWER_OF_TEN) { m_value = static_cast<int32_t>(value * std::pow(10, power_of_ten)) & 0xffffffe0 | power_of_ten & 0x1f; }
    void set(const double  value, const uint8_t power_of_ten = DEFAULT_POWER_OF_TEN) { m_value = static_cast<int32_t>(value * std::pow(10, power_of_ten)) & 0xffffffe0 | power_of_ten & 0x1f; }

    SimpleFixed& operator=(int32_t value) { set(value); return *this; }
    SimpleFixed& operator=(float value) { set(value); return *this; }
    SimpleFixed& operator=(double value) { set(value); return *this; }

    operator float()    const { return toFloat(); }
    operator double()   const { return toDouble(); }
    operator int32_t()  const { return static_cast<int32_t>(toFloat()); }
    operator int16_t()  const { return static_cast<int16_t>(toFloat()); }
    operator int8_t()   const { return static_cast<int8_t>(toFloat()); }
    operator uint32_t() const { return static_cast<uint32_t>(toFloat()); }
    operator uint16_t() const { return static_cast<uint16_t>(toFloat()); }
    operator uint8_t()  const { return static_cast<uint8_t>(toFloat()); }



private:
    int32_t m_value;
};
