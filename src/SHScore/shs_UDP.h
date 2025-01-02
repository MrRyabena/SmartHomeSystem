#pragma once


#include <stdint.h>
#include <functional>

#include <Arduino.h>
#ifdef ESP8266
#include <WiFiUdp.h>
#else
#include <WiFiUdp.h>
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
    class UdpBus;
    class UdpBroadcastBus;
    class UdpMulticastBus;
}


class shs::UDP : public shs::Process
{
public:
#if defined(SHS_SF_ESP8266) || defined(SHS_SF_ESP32)
    using UDP_t = WiFiUDP;
#else
#endif

    UDP_t udp;

    using Status = shs::DTPbus::Status;

    UDP(const UDP& other) : udp(other) {}
    UDP& operator=(const UDP& rhs) { udp = rhs.udp; return *this; }


    // UDP
    static Status checkBus(UDP_t& udp, shs::ByteCollector<>& buf, uint8_t& len, shs::API* handler)
    {
        if (udp.parsepacket())
        {
            auto status = shs::DTPbus::processBus(udp, buf, len);
            return shs::DTPbus::processPacket(buf, status, handler);
        }
    }
    Status checkBus(shs::ByteCollector<>& buf, uint8_t& len) { return checkBus(udp, buf, len); }

    static uint8_t sendBroadcastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendPacket(udp, packet, shs::settings::DEFAULT_BROADCAST_IP, port); }
    static uint8_t sendBroadcastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(udp, bc, shs::settings::DEFAULT_BROADCAST_IP, port); }
    static uint8_t sendBroadcastRAW(UDP_t& udp, shs::ByteCollectorIterator<>& it, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(udp, it, shs::settings::DEFAULT_BROADCAST_IP, port); }
    static uint8_t sendBroadcastRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(udp, data, size, shs::settings::DEFAULT_BROADCAST_IP, port); }

    uint8_t sendBroadcastPacket(const shs::DTPpacket& packet, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastPacket(udp, packet); }
    uint8_t sendBroadcastRAW(shs::ByteCollector<>& bc, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastRAW(udp, bc); }
    uint8_t sendBroadcastRAW(shs::ByteCollectorIterator<>& it, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastRAW(udp, it); }
    uint8_t sendBroadcastRAW(const uint8_t* data, const uint8_t size, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendBroadcastRAW(udp, data, size); }


    static uint8_t sendMulticastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginMulticastPacket(multicastIP, port, WiFi.mode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
        auto out = shs::DTPbus::sendPacket(udp, packet);
        udp.endPacket();

        return out;
    }

    static uint8_t sendMulticastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginMulticastPacket(multicastIP, port, WiFi.mode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
        auto out = shs::DTPbus::sendRAW(udp, bc);
        udp.endPacket();

        return out;
    }

    static uint8_t sendMulticastRAW(UDP_t& udp, shs::ByteCollectorIterator<>& it, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginMulticastPacket(multicastIP, port, WiFi.mode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
        auto out = shs::DTPbus::sendRAW(udp, it);
        udp.endPacket();

        return out;
    }

    static uint8_t sendMulticastRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginMulticastPacket(multicastIP, port, WiFi.mode() == WIFI_STA ? WiFi.localIP() : WiFi.softAPIP())) return 0;
        auto out = shs::DTPbus::sendRAW(udp, data, size);
        udp.endPacket();

        return out;
    }

    uint8_t sendMulticastPacket(const shs::DTPpacket& packet, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastPacket(udp, packet, multicastIP, port); }
    uint8_t sendMulticastRAW(shs::ByteCollector<>& bc, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastRAW(udp, bc, multicastIP, port); }
    uint8_t sendMulticastRAW(shs::ByteCollectorIterator<>& it, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastRAW(udp, it, multicastIP, port); }
    uint8_t sendMulticastRAW(const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendMulticastRAW(data, size, multicastIP, port); }


    static uint8_t sendPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginPacket(IP, port)) return 0;
        auto out = shs::DTPbus::sendPacket(udp, packet);
        udp.endPacket();

        return out;
    }

    static uint8_t sendRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginPacket(IP, port)) return 0;
        auto out = shs::DTPbus::sendRAW(udp, bc);
        udp.endPacket();

        return out;
    }

    static uint8_t sendRAW(UDP_t& udp, shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginPacket(IP, port)) return 0;
        auto out = shs::DTPbus::sendRAW(udp, it);
        udp.endPacket();

        return out;
    }
    static uint8_t sendRAW(UDP_t& udp, const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT)
    {
        if (!udp.beginPacket(IP, port)) return 0;
        auto out = shs::DTPbus::sendRAW(udp, data, size);
        udp.endPacket();

        return out;
    }

    uint8_t sendPacket(const shs::DTPpacket& packet, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendPacket(packet, IP, port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(bc, IP, port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(it, IP, port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { return sendRAW(data, size, IP, port); }


    // shs::Process
    void start() override {}
    void tick() override {}
    void stop() override {}
};


class shs::UdpBus : public shs::DTPbus
{
    explicit UdpBus(const shs::t::IP_t ip, const shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : DTPbus(busID, handler, bufsize), m_ip(ip), m_port(port)
    {}

    UdpBus(UdpBus&& other) : DTPbus(other), m_ip(ip), m_port(port) {}

    ~UdpBus() = default;


    // DTPbus
    Status checkBus() override { return shs::UDP::checkBus(m_udp, m_bc, m_len, m_handler); }


    // sending data
    uint8_t sendPacket(const shs::DTPpacket& packet) override { m_udp.sendPacket(packet, m_ip, m_port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { m_udp.sendRAW(bc, m_ip, m_port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { m_udp.sendRAW(it, m_ip, m_port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { m_udp.sendRAW(data, size, m_ip, m_port); }


    // shs::Process (from DTPbus)
    void start() override { m_udp.start(); m_udp.udp.begin(m_port); }
    void tick() override { m_udp.tick(); }
    void stop() override { m_udp.stop(); }

protected:
    shs::t::shs_IP_t m_ip;
    shs::t::shs_port_t m_port;
    shs::UDP m_udp;
};


class shs::UdpBroadcastBus : public shs::DTPbus
{
public:
    explicit UdpBroadcastBus(const shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : DTPbus(busID, handler, bufsize), m_port(port)
    {}

    UdpBroadcastBus(UdpBroadcastBus&& other) : DTPbus(other) {}

    ~UdpBroadcastBus() = default;

    // DTPbus
    Status checkBus() = 0;

    // sending data
    uint8_t sendPacket(const shs::DTPpacket& packet) override { m_udp.sendBroadcastPacket(packet, m_port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { m_udp.sendBroadcastRAW(bc, m_port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { m_udp.sendBroadcastRAW(it, m_port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { m_udp.sendBroadcastRAW(data, size, m_port); }


    // shs::Process (from DTPbus)
    void start() override { m_udp.start(); m_udp.udp.begin(m_port); }
    void tick() override { m_udp.tick(); }
    void stop() override { m_udp.stop(); }

protected:
    shs::UDP m_udp;
    shs::t::shs_port_t m_port;
};


class shs::UdpMulticastBus : public DTPbus
{
public:
    explicit UdpMulticastBus(const shs::t::shs_IP_t multicastIP shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : DTPbus(busID, handler, bufsize), m_multicastIP(multicastIP), m_port(port)
    {}

    UdpMulticastBus(UdpMulticastBus&& other) : DTPbus(other) {}

    ~UdpMulticastBus() = default;

    // DTPbus
    Status checkBus() = 0;

    // sending data
    uint8_t sendPacket(const shs::DTPpacket& packet) override { m_udp.sendMulticastPacket(packet, m_multicastIP, m_port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { m_udp.sendMulticastRAW(bc, m_multicastIP, m_port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { m_udp.sendMulticastRAW(it, m_multicastIP, m_port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { m_udp.sendMulticastRAW(data, size, m_multicastIP, m_port); }


    // shs::Process (from DTPbus)
    void start() override { m_udp.start(); m_udp.udp.begin(m_port); }
    void tick() override { m_udp.tick(); }
    void stop() override { m_udp.stop(); }

protected:
    shs::UDP m_udp;
    shs::t::shs_port_t m_port;
    shs::t::shs_IP_t m_multicastIP;
};
