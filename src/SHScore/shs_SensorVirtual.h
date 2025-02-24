#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — moved to a separate file, redesigned, debugged and tested.
*/

/*
  The "handler" class controls the load on the module itself.
  The "virtual" class implements the interface on the remote device.
*/

#include <memory>

#include "shs_Sensor.h"
#include "shs_Sensor_API.h"
#include "shs_types.h"
#include "shs_APIids.h"
#include "shs_API.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_DTP.h"
#include "shs_DTPpacket.h"


namespace shs
{
    class SensorVirtual;
}


class shs::SensorVirtual : public shs::Sensor, public shs::API
{
public:
    explicit SensorVirtual(shs::t::shs_ID_t thisID, shs::t::shs_ID_t virtualID, shs::DTP& dtp, const shs::Sensor::Type stype = UNKNOWN)
        : Sensor(stype), API(thisID.setComponentID(shs::constants::APIids::Sensor)), m_virtualID(virtualID.setComponentID(shs::constants::APIids::Sensor)), m_dtp(dtp)
    {}

    ~SensorVirtual() = default;

    // API
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    // Sensor
    void setup() override {}
    void update() override;
    void updateFast() override;

    [[nodiscard]] bool isUpdated() override { return m_updatedFlag; }
    [[nodiscard]] uint8_t getStatus() override { return 0; }

    [[nodiscard]] int32_t              getValueI([[maybe_unused]] const uint8_t metric = 0) override { return static_cast<int32_t>(m_value); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx([[maybe_unused]] const uint8_t metric = 0) override { return m_value; }
    [[nodiscard]] shs::t::shs_float_t  getValueF([[maybe_unused]] const uint8_t metric = 0) override { return static_cast<shs::t::shs_float_t>(m_value); }
    [[nodiscard]] shs::t::shs_double_t getValueD([[maybe_unused]] const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(m_value); }

protected:
    shs::t::shs_ID_t m_virtualID;
    shs::DTP& m_dtp;

    shs::t::shs_fixed_t m_value{};
    bool m_updatedFlag{};
};
