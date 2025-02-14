#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — corrected.
    v1.0.0 — release.
*/

/*
  The server class for processing clients.
*/

#include <memory>


#include "shs_settings_private.h"

#if defined(SHS_SF_NETWORK) && defined(SHS_SF_ARDUINO)


#ifdef SHS_SF_ARDUINO
#include <Arduino.h>

#ifdef SHS_SF_ESP8266
#include <ESP8266WiFi.h>
#elif defined(SHS_SF_ESP32)
#include <WiFi.h>
#endif

#ifdef SHS_SF_ESP
#include <WiFiServer.h>
#include <WiFiClient.h>
#endif
#endif

#include "shs_Process.h"
#include "shs_DTP.h"
#include "shs_APIids.h"
#include "shs_DTPpacket.h"
#include "shs_TcpSocket.h"


namespace shs
{
    class TcpServer;
};


class shs::TcpServer : public shs::Process
{
public:
    WiFiServer server;
    static constexpr auto max_connection_time = 2000;

    explicit TcpServer(const IPAddress& hostIP, const uint16_t port, shs::DTP& dtp)
        : server(hostIP, port), m_dtp(dtp)
    {}

    explicit TcpServer(const uint16_t port, shs::DTP& dtp)
        : server(port), m_dtp(dtp)
    {}

    ~TcpServer() = default;

    // -------------------- shs::Process ---------------------------------------
    void start() override { server.begin(); };
    void tick() override;
    void stop() override {}

private:
    shs::DTP& m_dtp;
    std::unique_ptr<shs::TcpSocket> m_connecting_client{};
    size_t m_connecting_client_time{};
};
#endif  // #ifdef SHS_SF_NETWORK
