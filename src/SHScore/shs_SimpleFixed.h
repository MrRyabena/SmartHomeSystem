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
    SimpleFixed(shs::t::shs_double_t value, uint8_t power_of_ten = 4) noexcept
        : m_value(static_cast<int32_t>(value* std::pow(10, power_of_ten)) & 0xffffffe0 | power_of_ten & 1f)
    {}

    shs::t::shs_float_t toFloat() const { return static_cast<shs::t::shs_float_t>(m_value & 0xffffffe0) * m_value & 1f; }
    shs::t::shs_double_t toDouble() const { return static_cast<shs::t::shs_double_t>(m_value & 0xffffffe0) * m_value & 1f; }


    operator int()      noexcept const { return static_cast<int>(toFloat()); }
    operator float()    noexcept const { return static_cast<float>(toFloat()); }
    operator double()   noexcept const { return toDouble(); }
    operator int32_t()  noexcept const { return static_cast<int32_t>(toFloat()); }
    operator int16_t()  noexcept const { return static_cast<int16_t>(toFloat()); }
    operator int8_t()   noexcept const { return static_cast<int8_t>(toFloat()); }
    operator uint32_t() noexcept const { return static_cast<uint32_t>(toFloat()); }
    operator uint16_t() noexcept const { return static_cast<uint16_t>(toFloat()); }
    operator uint8_t()  noexcept const { return static_cast<uint8_t>(toFloat()); }

private:
    int32_t m_value;
};
