#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  An abstract class to replace the Arduino Serial. Needed for DTP.
*/


#include <stdint.h>

namespace shs
{
    class Stream;
};

class shs::Stream
{
public:
    virtual uint8_t write(const uint8_t* buf, const uint16_t size) = 0;
    virtual uint8_t read() = 0;
    virtual uint8_t read(uint8_t* buf, const uint16_t size) = 0;
    virtual uint8_t available() = 0;
};
