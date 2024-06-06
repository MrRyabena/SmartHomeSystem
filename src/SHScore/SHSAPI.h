#pragma once

/*
  Last update: v0.1.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
    v2.0.0 — changed types, using shs::ID.
*/

/*
  This is an abstract class of API-handler.
  If you want to create your API-class for something, you must inherit from shs::API.
*/

#include <stdint.h>
#include "SHSByteCollector.h"
#include "SHStypes.h"

namespace shs
{
    class API;
};

class shs::API
{
public:
    explicit API(const shs::t::shs_ID_t id) : m_API_ID(id) {}

    virtual uint8_t handler(shs::ByteCollector &data) = 0;

protected:
    shs::t::shs_ID_t m_API_ID{};
};
