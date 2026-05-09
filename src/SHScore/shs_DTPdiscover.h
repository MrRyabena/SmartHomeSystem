#pragma once


/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created a new component of DTP.
    v2.3.0 — using shs_moduleID_t for id, updated docs.
*/

#include "shs_settings_private.h"

#if defined(SHS_SF_NETWORK) && !defined(SHS_SF_AVR)


#include <memory> 
#include <stdint.h>


#include "shs_UDPbus.h"
#include "shs_Process.h"
#include "shs_types.h"
#include "shs_ProgramTime.h"
#include "shs_SortedBuf.h"
#include "shs_API.h"
#include "shs_APIids.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"

#include "shs_debug.h"

#ifdef SHS_SF_ESP
#include "shs_ControlWiFi.h"
#endif

namespace shs
{
    class DTPdiscover;
}


/**
 * @brief DTP discovery helper that searches for devices on the local network.
 */
class shs::DTPdiscover : public shs::Process, public shs::API
{
public:
    /**
     * @brief Creates a discovery helper for the given module ID and UDP port.
     */
    DTPdiscover(shs::t::shs_ID_t moduleID, const shs::t::shs_port_t udp_broadcast_port = shs::settings::DEFAULT_UDP_PORT)
        : API(moduleID.setComponentID(shs::constants::APIids::DTPdiscover)), m_udp_broadcast(udp_broadcast_port, 1)
    {}

    static constexpr uint16_t MAX_WAIT_TIME = 15000;

    /**
     * @brief Starts discovery for a single device ID.
     * @param id Searched device ID.
     */
    void discover(shs::t::shs_moduleID_t id);

    /**
     * @brief Starts discovery for all known devices.
     */
    void discoverAll();

    /**
     * @brief Starts discovery and waits for the device to respond.
     * @param id Searched device ID.
     * @param max_time Maximum time to wait for a response.
     * @return Discovered IP address or default if not found.
     */
    shs::t::shs_IP_t discoverWait(shs::t::shs_moduleID_t id, const uint16_t max_time);

    /**
     * @brief Returns the discovered IP for the given device ID.
     */
    shs::t::shs_IP_t check(const shs::t::shs_moduleID_t id);


    enum Commands { NOCOMMAND, GET_IP, IP };


    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    void start() override { m_udp_broadcast.start(); }
    void tick() override;
    void stop() override { m_udp_broadcast.stop(); }

    /**
     * @brief Prints the collected discovery results.
     */
    void printAllDiscovered()
    {
        for (auto& data : m_requests)
        {
            dout("id: ");
            dout(data.id);
            dout("  ip: ");
            doutln(static_cast<uint32_t>(data.ip));
        }
    }

protected:
    struct m_Data
    {
        m_Data(const shs::t::shs_moduleID_t set_id, const shs::t::shs_IP_t set_ip = {})
            : id(set_id), ip(set_ip), timer()
        {}

        shs::t::shs_moduleID_t id;
        shs::t::shs_IP_t ip;
        shs::ProgramTime timer;

        bool operator<(const m_Data& other) const { return id < other.id; }
    };

    struct m_Data_less
    {
        inline bool operator()(const shs::DTPdiscover::m_Data& lhs, const shs::DTPdiscover::m_Data& rhs) const { return lhs.id < rhs.id; }
    };

    shs::UdpBroadcastBus m_udp_broadcast;
    shs::SortedBuf<shs::DTPdiscover::m_Data, shs::DTPdiscover::m_Data_less> m_requests;
};

#endif  // defined(SHS_SF_NETWORK) && !defined(SHS_SF_ESP32)
