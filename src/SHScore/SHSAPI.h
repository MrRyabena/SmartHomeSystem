#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>
#include "SHSByteCollector.h"

namespace shs
{
    class API;
};

class shs::API
{
public:
    API(int16_t ID = 0) : m_ID(ID) {}

    void setID(int16_t ID) { m_ID = ID; }
    int16_t getID() { return m_ID; }

    virtual uint8_t handler(shs::ByteCollector &data);

protected:
    int16_t m_ID{};
};
