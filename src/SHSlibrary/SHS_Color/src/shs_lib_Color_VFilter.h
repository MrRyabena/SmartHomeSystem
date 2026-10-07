#pragma once

#include <stdint.h>

namespace shs::lib::Color
{
    class VFilter;
}


class shs::lib::Color::VFilter
{
public:
    virtual ~VFilter() = default;

    /**
     * @brief Apply the filter to the given value.
     * @param value The value to apply the filter to.
     * @return true if the value was changed, false otherwise.
     */
    virtual bool apply(uint8_t& value) = 0;
};
