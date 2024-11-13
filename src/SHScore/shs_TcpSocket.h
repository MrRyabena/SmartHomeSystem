#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
*/

/*
  There is no need for this class yet.
*/

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <stdint.h>
#include <functional>

#include "shs_Process.h"
#include "shs_types.h"
#include "shs_DTP_API.h"
#include "shs_Config.h"


namespace shs
{
    class TcpSocket;
};


class shs::TcpSocket : public shs::Process
{
public:
    WiFiClient client;

    explicit TcpSocket
    (
        const IPAddress& hostIP, const uint16_t port,
        const std::function<void(shs::TcpSocket&)>& connect_callback =
        [](shs::TcpSocket& socket) { auto packet = shs::DTP_APIpackets::getInitialPacket(shs::Config::moduleID); socket.client.write(packet.bc.getPtr(), packet.bc.size()); },
        const std::function<void(shs::TcpSocket&)>& disconnect_callback =
        [](shs::TcpSocket& socket) { socket.reconnect(); }
    ) : m_hostIP(hostIP), m_port(port), m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}


    explicit TcpSocket
    (
        const char* hostIP, const uint16_t port,
        const std::function<void(shs::TcpSocket&)>& connect_callback =
        [](shs::TcpSocket& socket) { auto packet = shs::DTP_APIpackets::getInitialPacket(shs::Config::moduleID); socket.client.write(packet.bc.getPtr(), packet.bc.size()); },
        const std::function<void(shs::TcpSocket&)>& disconnect_callback =
        [](shs::TcpSocket& socket) { socket.reconnect(); }
    )
        : m_port(port), m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {
        WiFi.hostByName(hostIP, m_hostIP);
    }

    virtual ~TcpSocket() = default;


    void reconnect() { m_connect(); }


    void start() override { client.connect(m_hostIP, m_port); }
    void tick() override { if (!client.connected()) m_disconnect_callback(*this); }
    void stop() override { client.stop(); }


    IPAddress getIP() const { return m_hostIP; }
    uint16_t getPort() const { return m_port; }

private:
    IPAddress m_hostIP;
    const uint16_t m_port;

    std::function<void(shs::TcpSocket& client)> m_connect_callback;
    std::function<void(shs::TcpSocket& client)> m_disconnect_callback;

    void m_connect() { if (client.connect(m_hostIP, m_port)) m_connect_callback(*this); }
};
