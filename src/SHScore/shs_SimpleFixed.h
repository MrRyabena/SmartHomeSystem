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

    shs::t::shs_float_t getFloat() const { return static_cast<shs::t::shs_float_t>(m_value & 0xffffffe0) * m_value & 1f; }
    shs::t::shs_double_t getDouble() const { return static_cast<shs::t::shs_double_t>(m_value & 0xffffffe0) * m_value & 1f; }

private:
    int32_t m_value;
};
