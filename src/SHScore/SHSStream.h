#pragma once
#include <stdint.h>

namespace shs
{
    class Stream;
};

class shs::Stream
{
public:
    virtual uint8_t write(const uint8_t *buf, size_t size) = 0;
    virtual uint8_t read() = 0;
    virtual uint8_t available() = 0;
};
