#pragma once

#include <stdint.h>

namespace shs
{
    namespace errors
    {
        enum Errors : uint8_t;
    };
};

enum shs::errors::Errors : uint8_t
{
    OK,
    DTP_TIMEOUT,
    DTP_CRC,
    DTP_PROCESSED,
    DTP_INVALIDaddress,
    DTP_PTRerror,
    DTP_CMDerror,
};
