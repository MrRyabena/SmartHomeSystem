#pragma once

#include <shs_APIids.h>

namespace shs
{
    namespace lib
    {
        enum class APIids : uint16_t;
    }
}


enum class shs::lib::APIids : uint16_t
{
    SHS_LIBRARY_IDs = 0x4000,
    GRGB_API,
};
