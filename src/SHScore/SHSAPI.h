#pragma once

/*
  Last update: v0.1.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
*/

/*
  This is an abstract class of API-handler.
  If you want to create your API-class for something, you must inherit from shs::API.
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
