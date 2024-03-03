#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  The "handler" class controls the load on the module itself.
  The "virtual" class implements the interface on the remote device.
*/

#include "SHSAPI.h"
#include "SHSLoad.h"
#include "SHSsettings_private.h"
#include "SHSByteCollector.h"
#include "SHSModule.h"
#include "SHSerrors.h"

namespace shs
{
    namespace LoadAPIcmds
    {
        enum LoadAPIcmds : uint8_t;
    };
    class LoadAPIvirtual;
    class LoadAPIhandler;
}

enum shs::LoadAPIcmds::LoadAPIcmds : uint8_t
{
    Lon8,
    Lon16,
    Loff,
};

class shs::LoadAPIvirtual : public shs::API, public shs::Load
{
public:
    LoadAPIvirtual(const shs::settings::shs_ID_t ID = 0, const shs::settings::shs_ModuleID_t to = 0);

    void setup() override {}

    void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;
    void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    uint8_t handler(shs::ByteCollector &data) override { return 0; }
};

class shs::LoadAPIhandler : public shs::API
{
public:
    LoadAPIhandler(const shs::settings::shs_ID_t ID = 0, const shs::settings::shs_ModuleID_t to = 0,
                   shs::Load *loads = nullptr);

    uint8_t handler(shs::ByteCollector &data) override;

protected:
    shs::Load *m_loads{};
};
