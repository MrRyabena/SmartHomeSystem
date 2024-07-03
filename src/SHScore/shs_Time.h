#pragma once

#include <stdint.h>

namespace shs
{
    struct Time;
}

struct shs::Time
{
    uint32_t unixTime{};
    
    uint16_t getYear() ;

    // uint16_t year{};
    // uint8_t month{};
    // uint8_t day{};
    // uint8_t hour{};
    // uint8_t minute{};
    // uint8_t second{};
    // uint8_t dayOfWeek{};
};
