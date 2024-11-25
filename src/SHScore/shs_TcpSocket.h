#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
*/


#include <stdint.h>
#include <functional>

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "shs_Process.h"
#include "shs_types.h"
#include "shs_DTP_API.h"
#include "shs_DTPbus.h"
#include "shs_types.h"
#include "shs_API.h"


namespace shs
{
    class TcpSocket;
};


class shs::TcpSocket : public shs::DTPbus
{
public:
    WiFiClient client;


    using default_connect_callback = [](shs::TcpSocket& socket)
        { auto packet = shs::DTP_APIpackets::getInitialPacket(socket.busID); socket.client.write(packet.bc.getPtr(), packet.bc.size()); };
    using default_disconnect_callback = [](shs::TcpSocket& socket) { socket.reconnect(); };


    explicit TcpSocket
    (
        const IPAddress& hostIP, const uint16_t port,
        const shs::t::shs_ID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
    )
        :
        m_hostIP(hostIP), m_port(port),
        DTPbus(busID, handler, bufsize),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}


    explicit TcpSocket
    (
        const char* hostIP, const uint16_t port,
        const shs::t::shs_ID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
    )
        :
        m_port(port),
        DTPbus(busID, handler, bufsize),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {
        WiFi.hostByName(hostIP, m_hostIP);
    }

    explicit TcpSocket
    (
        const WiFiClient& other,
        const shs::t::shs_ID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
    )
        :
        client(other), m_port(0),
        DTPbus(busID, handler, bufsize),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}

    virtual ~TcpSocket() = default;

    // native functions

    void reconnect() { m_connect(); }

    IPAddress getIP() const { return m_hostIP; }
    uint16_t getPort() const { return m_port; }


    // inherited from shs::Process (from shs::DTPbus)
    void start() override { client.connect(m_hostIP, m_port); }
    void tick() override { if (!client.connected()) m_disconnect_callback(*this); }
    void stop() override { client.stop(); }


    // inherited from shs::DTPbus
    uint8_t checkBus() override { processBus(client); processPacket(); }
    uint8_t sendPacket(shs::DTPpacket& packet) override { return client.write(packet.bc.getPtr(), packet.bc.size()); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return client.write(bc.getPtr(), bc.size()); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return client.write(it.getPtr(), it.size()); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return client.write(data, size); }


private:
    IPAddress m_hostIP;
    const uint16_t m_port;

    std::function<void(shs::TcpSocket& client)> m_connect_callback;
    std::function<void(shs::TcpSocket& client)> m_disconnect_callback;

    void m_connect() { if (client.connect(m_hostIP, m_port)) m_connect_callback(*this); }
};
