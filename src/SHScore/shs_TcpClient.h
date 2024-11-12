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
#include "shs_Stream.h"
#include "shs_Config.h"


namespace shs
{
    class TcpClient;

};


class shs::TcpClient : public shs::Process, public shs::Stream
{
public:
    WiFiClient client;

    TcpClient
    (
        const IPAddress hostIP, const uint16_t port,
        const std::function<void(shs::TcpClient& client)>& connect_callback =
        [](shs::TcpClient& client) { auto packet = shs::DTP_APIpackets::getInitialPacket(shs::Config::moduleID); client.write(packet.bc.getPtr(), packet.bc.size()); },
        const std::function<void(shs::TcpClient& client)>& disconnect_callback = [](shs::TcpClient& client) { client.reconnect(); }
    ) : m_hostIP(hostIP), m_port(port), m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}


    TcpClient(const char* hostIP, const uint16_t port, const std::function<void(shs::TcpClient& client)>& connect_callback)
        : m_port(port), m_connect_callback(connect_callback)
    {
        WiFi.hostByName(hostIP, m_hostIP);
    }

    virtual ~TcpClient() = default;


    void reconnect() { client.connect(m_hostIP, m_port); }


    void start() override { m_flags.set(ACTIVE); client.connect(m_hostIP, m_port); }
    void tick() override { if (!client.connected()) m_disconnect_callback(); }
    void stop() override { m_flags.set(ACTIVE, false); client.stop(); }


    uint8_t read() override { return client.read(); }
    uint8_t read(uint8_t* buf, const uint16_t size) override { return client.read(buf, size); }
    uint8_t write(const uint8_t* buf, const uint16_t) override { return client.write(buf, size); }
    uint8_t available() override { return client.available(); }


    IPAddress getIP() const { return m_hostIP; }
    uint16_t getPort() const { return m_port; }

private:
    IPAddress m_hostIP;
    const uint16_t m_port;

    std::function<void(shs::TcpClient& client)> m_connect_callback;
    std::function<void(shs::TcpClient& client)> m_disconnect_callback;

    void m_connect() { if (client.connect(m_hostIP, m_port)) m_connect_callback(); }
};
