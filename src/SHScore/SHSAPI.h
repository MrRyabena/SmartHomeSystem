#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>
#include "SHSByteCollector.h"
#include "SHSsettings_private.h"
#include "SHSDTP.h"

namespace shs
{
    class APIvirtual;
    class APIhandler;
};

class shs::APIvirtual
{
    explicit APIvirtual(const shs::settings::shs_ID_t apiID = 0, const shs::settings::shs_ModuleID_t to = 0, shs::DTP *dtp = nullptr)
        : m_ID(ID), m_to(to), m_dtp(dtp) {}

    void setID(const shs::settings::shs_ID_t ID) { m_ID = ID; }
    shs::settings::shs_ID_t getID() const { return m_ID; }

protected:
    shs::settings::shs_ID_t m_ID{};
    shs::settings::shs_ModuleID_t m_to{};
    shs::DTP *m_dtp{};
};

class shs::APIhandler
{
public:
    API(const shs::settings::shs_ID_t ID = 0, shs::DTP *dtp = nullptr)
        : m_ID(ID) {}

    void setID(const shs::settings::shs_ID_t ID) { m_ID = ID; }
    shs::settings::shs_ID_t getID() const { return m_ID; }

    virtual uint8_t handler(shs::ByteCollector &data) = 0;

protected:
    shs::settings::shs_ID_t m_ID{};
    shs::DTP *m_dtp{};
};
