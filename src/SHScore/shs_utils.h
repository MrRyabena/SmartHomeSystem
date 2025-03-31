#pragma once


/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/


#include <type_traits>


namespace shs
{
    template <typename EnumT>
    constexpr auto etoi(EnumT value) { return static_cast<std::underlying_type_t<EnumT>>(value); }
}
