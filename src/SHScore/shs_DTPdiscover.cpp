#include "shs_DTPdiscover.h"

#if defined(SHS_SF_NETWORK) && !defined(SHS_SF_ESP32)


void shs::DTPdiscover::discover(const uint8_t id)
{
    shs::ByteCollector<> buf(1);
    buf.push_back(GET_IP, 1);

    m_udp_broadcast.sendPacket(shs::DTPpacket(API_ID, shs::t::shs_ID_t(id), std::move(buf)));
    m_requests.attach(m_Data(id));
}


shs::t::shs_IP_t shs::DTPdiscover::discoverWait(const uint8_t id, const uint16_t max_time)
{
    discover(id);
    shs::ProgramTime timer;

#ifdef SHS_SF_QT
    while (timer.milliseconds() < max_time)
    {
        m_udp_broadcast.getUdpPtr()->udp.getQUdpPtr()->waitForReadyRead(max_time);
        tick();
        auto ip = check(id);
        if (ip != 0u) return ip;
    }
#else
    while (timer.milliseconds() < max_time)
    {
        tick();
        auto ip = check(id);
        if (ip != 0u) return ip;
    }
#endif

    return 0u;
}


shs::t::shs_IP_t shs::DTPdiscover::check(const uint8_t id)
{
    auto res = m_requests.get(m_Data(id));

    if (res != m_requests.end()) return res->ip;

    return 0u;
}


shs::DTPpacket shs::DTPdiscover::handle(shs::ByteCollectorReadIterator<>& it)
{
    if (shs::DTPpacket::get_senderID(it) == API_ID) return shs::DTPpacket();

    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case Commands::IP:
            {
                auto id = shs::DTPpacket::get_senderID(it);
                shs::t::shs_IP_t ip{};
                it.get(ip);

                auto req = m_requests.get(m_Data(id.getModuleID()));


                if (req != m_requests.end()) m_requests.detach(*req);
                m_requests.attach(m_Data(id.getModuleID(), ip));
            }
            break;

        case Commands::GET_IP:
            {
            #ifdef SHS_SF_ESP
                shs::ByteCollector<> bc(5);
                bc.push_back(Commands::IP, 1);
                shs::IP ip(shs::ControlWiFi::localIP());
                bc.push_back(static_cast<uint32_t>(ip));

                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            #endif  
                // temporarily not implemented

            }
            break;

        default: break;
    }

    return shs::DTPpacket();
}


void shs::DTPdiscover::tick()
{
    for (auto& x : m_requests) if (x.timer.milliseconds() > MAX_WAIT_TIME) m_requests.detach(x);

    m_udp_broadcast.tick();
    if (m_udp_broadcast.checkBus() == shs::DTPbus::packet_received || m_udp_broadcast.status == shs::DTPbus::packet_processed)
    {
        auto it = m_udp_broadcast.getLastData();
        auto answer = handle(it);

        m_udp_broadcast.sendPacket(answer);
    }
}


#endif  // #if defined(SHS_SF_NETWORK) && !defined(SHS_SF_ESP32)
