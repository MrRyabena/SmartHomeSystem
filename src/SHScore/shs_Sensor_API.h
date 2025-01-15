#pragma once

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
        : API(id.setApiID(shs::constants::APIids::Sensor)), m_sensor(sensor), m_dtp(dtp)
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
