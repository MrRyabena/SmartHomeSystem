#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/


#include "shs_UDP.h"


namespace shs
{
    class UdpBus;
    class UdpBroadcastBus;
    class UdpMulticastBus;
}


class shs::UdpBus : public shs::DTPbus
{
    explicit UdpBus(const shs::t::shs_IP_t ip, const shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : DTPbus(busID, handler, bufsize), m_ip(ip), m_port(port)
    {}

    UdpBus(UdpBus&& other) : DTPbus(std::move(other)), m_ip(other.m_ip), m_port(other.m_port) {}

    ~UdpBus() = default;


    // DTPbus
    shs::DTPbus::Status checkBus() override { return shs::DTPbus::checkBus(m_udp.udp); }


    // sending data
    uint8_t sendPacket(const shs::DTPpacket& packet) override { return m_udp.sendPacket(packet, m_ip, m_port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return m_udp.sendRAW(bc, m_ip, m_port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return m_udp.sendRAW(it, m_ip, m_port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return m_udp.sendRAW(data, size, m_ip, m_port); }


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
    {
        connected_modules.attach(0xff);
    }

    UdpBroadcastBus(UdpBroadcastBus&& other) : DTPbus(std::move(other)) {}

    ~UdpBroadcastBus() = default;

    // DTPbus
    bool isActive() const override { return true; }

    shs::DTPbus::Status checkBus() override { return shs::DTPbus::checkBus(m_udp.udp); }

    // sending data
    uint8_t sendPacket(const shs::DTPpacket& packet) override { return m_udp.sendBroadcastPacket(packet, m_port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return m_udp.sendBroadcastRAW(bc, m_port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return m_udp.sendBroadcastRAW(it, m_port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return m_udp.sendBroadcastRAW(data, size, m_port); }

    shs::UDP* getUdpPtr() { return &m_udp; }

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
    explicit UdpMulticastBus(const shs::t::shs_IP_t multicastIP, shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25)
        : DTPbus(busID, handler, bufsize), m_multicastIP(multicastIP), m_port(port)
    {}

    UdpMulticastBus(UdpMulticastBus&& other) : DTPbus(std::move(other)) {}

    ~UdpMulticastBus() = default;

    // DTPbus
    shs::DTPbus::Status checkBus() override { return shs::DTPbus::checkBus(m_udp.udp); }

    // sending data
    uint8_t sendPacket(const shs::DTPpacket& packet) override { return m_udp.sendMulticastPacket(packet, m_multicastIP, m_port); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return m_udp.sendMulticastRAW(bc, m_multicastIP, m_port); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return  m_udp.sendMulticastRAW(it, m_multicastIP, m_port); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return m_udp.sendMulticastRAW(data, size, m_multicastIP, m_port); }


    // shs::Process (from DTPbus)
    void start() override { m_udp.start(); m_udp.udp.begin(m_port); }
    void tick() override { m_udp.tick(); }
    void stop() override { m_udp.stop(); }

protected:
    shs::UDP m_udp;
    shs::t::shs_IP_t m_multicastIP;
    shs::t::shs_port_t m_port;
};
