#pragma once

#include "SHSAPI.h"
#include "SHSLoad.h"
#include "SHSsettings_private.h"
#include "SHSDTP.h"
#include "SHSByteCollector.h"

namespace shs
{
    enum LoadAPIcmds : uint8_t;
    class LoadAPIvirtual;
    class LoadAPIhandler;
}

enum shs::LoadAPIcmds : uint8_t
{
    on8,
    on16,
    off,
    size = 5;
};

class shs::LoadAPIvirtual : public shs::APIvirtual, public shs::Load
{
public:
    explicit LoadAPIVirtual(const shs::settings::shs_ID_t ID = 0, const shs::settings::shs_ModuleID_t to = 0, const shs::LoadType type = shs::LoadType::UNKNOWN, shs::DTP *dtp = nullptr);
    void setup() override{};

    void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;
    void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;
};

class shs::LoadAPIhandler : public shs::APIhandler
{
public:
    LoadAPI(shs::Load *loads);

    uint8_t handler(shs::ByteCollector &data) override;

protected:
    shs::Load *m_loads{};
};
