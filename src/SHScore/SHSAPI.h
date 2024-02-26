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
    explicit API(const shs::settings::shs_ID_t apiID = 0,
                 const shs::settings::shs_ModuleID_t to = 0)
        : m_apiID(apiID), m_to(to) {}

    virtual uint8_t handler(shs::ByteCollector &data) = 0;

protected:
    shs::settings::shs_ID_t m_apiID{};
    shs::settings::shs_ModuleID_t m_to{};
};
