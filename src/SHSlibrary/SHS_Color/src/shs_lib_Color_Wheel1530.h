#pragma once

#include <stdint.h>
#include <shs_algorithm.h>

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct Wheel1530;
        }
    }
}

/**
 * @brief Represents a color in Wheel format, using 16 bits for the wheel channel.
 * The structure provides constructors for creating colors from a wheel value or from a 32-bit integer representation.
 */
struct shs::lib::Color::Wheel1530
{
    explicit Wheel1530(const uint16_t value = 0)
        : wheel(shs::clamp(value, static_cast<uint16_t>(0), static_cast<uint16_t>(1530)))
    {}

    void setWheel(const uint16_t value)
    {
        wheel = shs::clamp(value, static_cast<uint16_t>(0), static_cast<uint16_t>(1530));
    }

    Wheel1530& operator++(int)
    {
        Wheel1530 temp = *this;
        ++wheel;
        if (wheel > 1530) wheel = 0;
        return temp;
    }

    Wheel1530& operator++()
    {
        ++wheel;
        if (wheel > 1530) wheel = 0;
        return *this;
    }

    Wheel1530& operator--(int)
    {
        Wheel1530 temp = *this;
        --wheel;
        if (wheel > 1530) wheel = 1530;
        return temp;
    }

    Wheel1530& operator--()
    {
        --wheel;
        if (wheel > 1530) wheel = 1530;
        return *this;
    }


    uint16_t wheel; /**< The wheel component (0-1530). */
};
