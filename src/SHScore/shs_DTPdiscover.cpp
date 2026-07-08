#include "shs_DTPdiscover.h"

#if defined(SHS_SF_NETWORK) && !defined(SHS_SF_AVR)


void shs::DTPdiscover::discover(const uint8_t id)
{


    // make sure we don't keep inserting the same id over and over
    // if a request for this module is already pending, just refresh its timer
    auto existing = m_requests.get(m_Data(id));
    if (existing == m_requests.end())
    {
        dout("discovering id: "); doutln(static_cast<int>(id));
        shs::ByteCollector<> buf(1);
        buf.push_back(GET_IP, 1);
        //shs::t::shs_ID_t(0xff, 0, 0) mask TODO
        m_udp_broadcast.sendPacket(shs::DTPpacket(API_ID, shs::t::shs_ID_t(id), std::move(buf)));
        m_requests.attach(m_Data(id));
    }
}


void shs::DTPdiscover::discoverAll()
{
    shs::ByteCollector<> buf(1);
    buf.push_back(GET_IP, 1);

    m_udp_broadcast.sendPacket(shs::DTPpacket(API_ID, 0, 0, std::move(buf)));
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

    return {};
}


shs::t::shs_IP_t shs::DTPdiscover::check(const uint8_t id)
{
    auto res = m_requests.get(m_Data(id));

    if (res != m_requests.end()) return res->ip;

    return {};
}


shs::DTPpacket shs::DTPdiscover::handle(shs::ByteCollectorReadIterator<>& it)
{
    if (it.size() == 0) { doutln("ret 72"); return shs::DTPpacket(); }
    if (shs::DTPpacket::get_senderID(it) == API_ID) { doutln("ret 73"); return shs::DTPpacket(); }
    if (shs::DTPpacket::get_DTPcode(it) == shs::DTPpacket::MASK)
    {
        doutln("ret 76");
        auto id = shs::DTPpacket::get_recipientID(it);
        auto mask = shs::DTPpacket::get_mask(it);

        
        // doitid(id); doutln();
        // doitid(API_ID.id); doutln();
        // doitid(mask); doutln();
        // doitid(id & mask); doutln();
        // doitid(API_ID.id & mask); doutln();
        // TODO !!!!!!!!!!!!!!
      //  if ((id & mask) != (API_ID.id & mask)) return shs::DTPpacket();
    }
    else if (shs::DTPpacket::get_recipientID(it).getModuleID() != API_ID.getModuleID()) { doutln("ret 82"); return shs::DTPpacket(); }

    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case Commands::IP:
            {
                doutln("NEW IP!");
                auto id = shs::DTPpacket::get_senderID(it);
                shs::t::shs_IP_t ip{};
                it.get(ip);
                dsep();
                dout("Module id: ");
                doutln(id.getModuleID());

                auto req = m_requests.get(m_Data(id.getModuleID()));

                // remove any existing entries matching this id (should be at most one,
                // but duplicates are possible if discover was called repeatedly)
                while (req != m_requests.end())
                {
                    m_requests.detach(*req);
                    req = m_requests.get(m_Data(id.getModuleID()));
                }

                m_requests.attach(m_Data(id.getModuleID(), ip));
            }
            break;

        case Commands::GET_IP:
            {
                doutln("GET IP!");

                shs::ByteCollector<> bc(5);
                bc.push_back(Commands::IP, 1);

#if defined(SHS_SF_ESP)
                shs::IP ip(shs::ControlWiFi::localIP());
#elif defined(SHS_SF_QT)
                shs::IP ip;
#else
                shs::IP ip(m_udp_broadcast.m_udp.udp.getQUdpPrt->localAddress());
#endif

                bc.push_back(static_cast<uint32_t>(ip));

                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;

        default: doutln("DEFAULT") break;
    }


    return shs::DTPpacket();
}


void shs::DTPdiscover::tick()
{
    for (auto& x : m_requests) if (x.timer.milliseconds() > MAX_WAIT_TIME) m_requests.detach(x);

    m_udp_broadcast.tick();
    if (m_udp_broadcast.checkBus() == shs::DTPbus::packet_received || m_udp_broadcast.status == shs::DTPbus::packet_processed)
    {
        doutln("has data!");
        auto it = m_udp_broadcast.getLastData();
        auto answer = handle(it);

        if (!answer.empty()) m_udp_broadcast.sendPacket(answer);
    }
}


#endif  // #if defined(SHS_SF_NETWORK) && !defined(SHS_SF_ESP32)
