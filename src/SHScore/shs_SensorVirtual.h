#pragma once

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
    explicit SensorVirtual(shs::t::shs_ID_t thisID, const shs::t::shs_ID_t virtualID, shs::DTP& dtp, const shs::Sensor::Type stype = UNKNOWN)
        : API(thisID.setApiID(shs::constants::APIids::Sensor)), Sensor(stype), m_virtualID(virtualID), m_dtp(dtp)
    {}

    ~SensorVirtual() = default;

    // API
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    // Sensor
    void update() override;
    void updateFast() override;

    bool isUpdated() override { return m_updatedFlag; }

    int32_t              getValueI() override { return static_cast<int32_t>(m_value); }
    shs::t::shs_float_t  getValueF() override { return static_cast<shs::t::shs_float_t>(m_value); }
    shs::t::shs_double_t getValueD() override { return static_cast<shs::t::shs_double_t>(m_value); }

protected:
    shs::t::shs_ID_t m_virtualID;
    shs::DTP& m_dtp;

    shs::t::shs_fixed_t m_value{};
    bool m_updatedFlag{};
};
