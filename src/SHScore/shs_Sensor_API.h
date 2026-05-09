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


#include "shs_settings_private.h"

#ifndef SHS_SF_AVR

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


/**
 * @brief API for exposing sensor metadata and readings over DTP.
 */
class shs::Sensor_API : public shs::API, public shs::Process
{
public:
    /**
     * @brief Creates a sensor API bound to a concrete sensor and DTP container.
        * @param sensor Sensor instance served by this API.
        * @param id Base ID used to build the API endpoint ID.
        * @param dtp DTP transport used for outgoing responses.
     */
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
    /**
     * @brief Handles sensor metadata and value requests.
        * @param it Iterator over incoming packet payload.
        * @return Response packet with type or data information, or empty packet when not needed.
     */
    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;


    // shs::Process
    /**
     * @brief Starts the sensor API process.
     */
    void start() override {}

    /**
     * @brief Periodically checks for incoming sensor requests.
     */
    void tick() override;

    /**
     * @brief Stops the sensor API process.
     */
    void stop() override {}

private:
    std::vector<shs::t::shs_ID_t> m_requestIDs;

    shs::DTP& m_dtp;
    shs::Sensor& m_sensor;
};


#endif    // #ifndef SHS_SF_AVR
