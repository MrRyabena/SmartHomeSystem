#pragma once


#include <stdint.h>
#include <functional>
#include <memory>

#include "shs_settings_private.h"

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#ifdef SHS_SF_ESP8266
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#elif defined(SHS_SF_ESP32)
#include <WiFiUdp.h>
#include <WiFi.h>
#endif

#elif defined(SHS_SF_QT)
#include "shs_qt_Udp.h"
#endif


#include "shs_Process.h"
#include "shs_types.h"
#include "shs_DTP_API.h"
#include "shs_DTPbus.h"
#include "shs_types.h"
#include "shs_API.h"
#include "shs_ProgramTime.h"


namespace shs
{
    class UDP;
}


class shs::UDP : public shs::Process
{
public:
#if defined(SHS_SF_ESP8266) || defined(SHS_SF_ESP32)
    using UDP_t = WiFiUDP;
#elif defined(SHS_SF_QT)
    using UDP_t = shs::qt::UdpSocket;
#endif

    UDP_t udp;

    using DTPstatus = shs::DTPbus::Status;

    UDP() {}

#ifndef SHS_SF_QT
    UDP(const UDP& other) : udp(other.udp) {}
    UDP& operator=(const UDP& rhs) { udp = rhs.udp; return *this; }
#endif

    // -------------------- Broadcast ------------------------------------------

    static uint8_t sendBroadcastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendPacket(udp, packet, shs::settings::DEFAULT_BROADCAST_IP, port); }
    static uint8_t sendBroadcastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(udp, bc, shs::settings::DEFAULT_BROADCAST_IP, port); }
    static uint8_t sendBroadcastRAW(UDP_t& udp, shs::ByteCollectorReadIterator<>& it, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(udp, it, shs::settings::DEFAULT_BROADCAST_IP, port); }
    static uint8_t sendBroadcastRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(udp, data, size, shs::settings::DEFAULT_BROADCAST_IP, port); }

    uint8_t sendBroadcastPacket(const shs::DTPpacket& packet, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastPacket(udp, packet); }
    uint8_t sendBroadcastRAW(shs::ByteCollector<>& bc, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastRAW(udp, bc); }
    uint8_t sendBroadcastRAW(shs::ByteCollectorReadIterator<>& it, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastRAW(udp, it); }
    uint8_t sendBroadcastRAW(const uint8_t* data, const uint8_t size, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastRAW(udp, data, size); }


    // -------------------- Multicast ------------------------------------------

    static uint8_t sendMulticastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
    static uint8_t sendMulticastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
    static uint8_t sendMulticastRAW(UDP_t& udp, shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
    static uint8_t sendMulticastRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);

    uint8_t sendMulticastPacket(const shs::DTPpacket& packet, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastPacket(udp, packet, multicastIP, port); }
    uint8_t sendMulticastRAW(shs::ByteCollector<>& bc, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastRAW(udp, bc, multicastIP, port); }
    uint8_t sendMulticastRAW(shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastRAW(udp, it, multicastIP, port); }
    uint8_t sendMulticastRAW(const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastRAW(data, size, multicastIP, port); }


    // -------------------- Unicast --------------------------------------------
    static uint8_t sendPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
    static uint8_t sendRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
    static uint8_t sendRAW(UDP_t& udp, shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
    static uint8_t sendRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);


    uint8_t sendPacket(const shs::DTPpacket& packet, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendPacket(packet, IP, port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(bc, IP, port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(it, IP, port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(data, size, IP, port); }


    // shs::Process
    void start() override {}
    void tick() override {}
    void stop() override {}
};
