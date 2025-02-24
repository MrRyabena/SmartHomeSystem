#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — redesigned, debugged and tested.
*/

/*
  The "handler" class controls the load on the module itself.
  The "virtual" class implements the interface on the remote device.
*/

#include <memory>
#include <vector>

#include "shs_API.h"
#include "shs_DTP.h"
#include "shs_Process.h"
#include "shs_Sensor.h"
#include "shs_types.h"
#include "shs_APIids.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"


namespace shs
{
    class Sensor_API;
}


class shs::Sensor_API : public shs::API, public shs::Process
{
public:
    explicit Sensor_API(shs::Sensor& sensor, shs::t::shs_ID_t id, shs::DTP& dtp) noexcept
        : API(id.setComponentID(shs::constants::APIids::Sensor)), m_dtp(dtp), m_sensor(sensor)
    {}

    enum Commands : uint8_t
    {
        NOCOMMAND,
        ERROR,
        GET_TYPE, TYPE,
        REQUEST_DATA, DATA
    };


    // shs::API
    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;


    // shs::Process
    void start() override {}
    void tick() override;
    void stop() override {}

private:
    std::vector<shs::t::shs_ID_t> m_requestIDs;

    shs::DTP& m_dtp;
    shs::Sensor& m_sensor;
};
