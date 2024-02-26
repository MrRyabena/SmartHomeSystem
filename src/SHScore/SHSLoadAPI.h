#pragma once

#include "SHSAPI.h"
#include "SHSLoad.h"
#include "SHSsettings_private.h"
#include "SHSByteCollector.h"
#include "SHSModule.h"

namespace shs
{
    enum LoadAPIcmds : uint8_t;
    class LoadAPIvirtual;
    class LoadAPIhandler;
}

enum shs::LoadAPIcmds : uint8_t
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
