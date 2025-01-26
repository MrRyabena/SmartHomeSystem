#include "shs_UDP.h"

/* -----------------------------------------------------------------------------
   Multicast
   -----------------------------------------------------------------------------
*/
uint8_t shs::UDP::sendMulticastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t multicastIP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO

    if (!udp.beginPacketMulticast(multicastIP, port, WiFi.getMode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
    auto out = shs::DTPbus::sendPacket(udp, packet);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return sendPacket(udp, packet, multicastIP, port);

#endif
}


uint8_t shs::UDP::sendMulticastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t multicastIP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO

    if (!udp.beginPacketMulticast(multicastIP, port, WiFi.getMode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
    auto out = shs::DTPbus::sendRAW(udp, bc);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return sendPacket(udp, bc, multicastIP, port);

#endif
}


uint8_t shs::UDP::sendMulticastRAW(UDP_t& udp, shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t multicastIP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO
    if (!udp.beginPacketMulticast(multicastIP, port, WiFi.getMode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
    auto out = shs::DTPbus::sendRAW(udp, it);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return sendPacket(udp, it, multicastIP, port);

#endif
}


uint8_t shs::UDP::sendMulticastRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
{
#ifdef SHS_SF_ARDUINO
    if (!udp.beginPacketMulticast(multicastIP, port, WiFi.getMode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
    auto out = shs::DTPbus::sendRAW(udp, data, size);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return sendPacket(udp, data, size, multicastIP, port);

#endif
}


/* -----------------------------------------------------------------------------
   Unicast
   -----------------------------------------------------------------------------
*/
uint8_t shs::UDP::sendPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO

    if (!udp.beginPacket(IP, port)) return 0;
    auto out = shs::DTPbus::sendPacket(udp, packet);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return udp.write(packet.bc.getPtr(), backet.bc.size(), multicastIP, port);

#endif
}


uint8_t shs::UDP::sendRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO

    if (!udp.beginPacket(IP, port)) return 0;
    auto out = shs::DTPbus::sendRAW(udp, bc);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return udp.write(bc.getPtr(), bc.size(), multicastIP, port);

#endif
}


uint8_t shs::UDP::sendRAW(UDP_t& udp, shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO

    if (!udp.beginPacket(IP, port)) return 0;
    auto out = shs::DTPbus::sendRAW(udp, it);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return udp.write(it.getPtr(), it.size(), multicastIP, port);

#endif
}


uint8_t shs::UDP::sendRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port)
{
#ifdef SHS_SF_ARDUINO

    if (!udp.beginPacket(IP, port)) return 0;
    auto out = shs::DTPbus::sendRAW(udp, data, size);
    udp.endPacket();

    return out;

#elif defined(SHS_SF_QT)

    return udp.write(data, size, multicastIP, port);

#endif
}
