#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>
#include "SHSByteCollector.h"
#include "SHSsettings_private.h"

namespace shs
{
    class API;
};

class shs::API
{
public:
    API(const shs::settings::shs_ID_t ID = 0) : m_ID(ID) {}

    void setID(const shs::settings::shs_ID_t ID) { m_ID = ID; }
    shs::settings::shs_ID_t getID() const { return m_ID; }

    virtual uint8_t handler(shs::ByteCollector &data) = 0;

protected:
    shs::settings::shs_ID_t m_ID{};
};
