#pragma once


#include <memory> 
#include <stdint.h>

#include "shs_settings_private.h"

#include "shs_UDPbus.h"
#include "shs_Process.h"
#include "shs_types.h"
#include "shs_ProgramTime.h"
#include "shs_SortedBuf.h"
#include "shs_API.h"
#include "shs_APIids.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"

#ifdef SHS_SF_ESP
#include "shs_ControlWiFi.h"
#endif


namespace shs
{
    class DTPdiscover;
}


class shs::DTPdiscover : public shs::Process, public shs::API
{
public:
    DTPdiscover(shs::t::shs_ID_t moduleID, const shs::t::shs_port_t udp_broadcast_port = shs::settings::DEFAULT_UDP_PORT)
        : API(moduleID.setApiID(shs::constants::APIids::DTPdiscover)), m_udp_broadcast(udp_broadcast_port, 1)
    {}

    static constexpr uint16_t MAX_WAIT_TIME = 5000;

    void discover(const uint8_t id);
    shs::t::shs_IP_t discoverWait(const uint8_t id, const uint16_t max_time);
    shs::t::shs_IP_t check(const uint8_t id);

    enum Commands { NOCOMMAND, GET_IP, IP };
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    void start() override { m_udp_broadcast.start(); }
    void tick() override;
    void stop() override { m_udp_broadcast.stop(); }


protected:
    struct m_Data
    {
        m_Data(const uint8_t set_id, const shs::t::shs_IP_t set_ip = 0u)
            : id(set_id), ip(set_ip), timer()
        {}

        uint8_t id;
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
