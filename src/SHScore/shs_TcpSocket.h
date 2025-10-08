#pragma once

/*
  Last update: v2.1.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
    v2.0.0 — updated functionality, debugged, tested.
      - It is based on shs::DTPbus.
      - Automatic reconnection in case of loss of connection.
      - Qt support.
    v2.1.0 — fixed bugs related to shs::DTP_API.
*/

#include "shs_settings_private.h"

#if defined(SHS_SF_NETWORK)


#include <stdint.h>
#include <functional>

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>


#ifdef SHS_SF_ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#elif defined(SHS_SF_QT)
#include "shs_qt_TcpSocket.h"
#include <QObject>
#endif

#include "shs_Process.h"
#include "shs_types.h"
#include "shs_DTP_API.h"
#include "shs_DTPbus.h"
#include "shs_types.h"
#include "shs_API.h"
#include "shs_ProgramTime.h"
#include "shs_ProgramTimer.h"

namespace shs
{
    class TcpSocket;
};

class shs::TcpSocket : public shs::DTPbus
{
public:
#ifdef SHS_SF_ARDUINO
    WiFiClient client;
#elif defined(SHS_SF_QT)
    shs::qt::TcpSocket client;
#endif

    enum Status : uint8_t
    {
        DISCONNECTED,
        CONNECTING,
        RECONNECTING,
        CONNECTED,
        INACTIVE
    };

    static std::function<void(shs::TcpSocket&)> default_connect_callback;
    static std::function<void(shs::TcpSocket&)> default_disconnect_callback;

    explicit TcpSocket(
        const shs::t::shs_IP_t& hostIP, shs::t::shs_port_t port,
        shs::t::shs_busID_t busID, shs::API* handler = nullptr, uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback);

    explicit TcpSocket(
    #ifdef SHS_SF_ARDUINO
        const WiFiClient& parent,
    #elif defined(SHS_SF_QT)
        QObject* parent,
        const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
    #endif
        shs::t::shs_busID_t busID, shs::API* handler = nullptr, uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback);

    ~TcpSocket() = default;

    // -------------------- native functions -----------------------------------

    void connect(shs::t::shs_time_t connecting_timeout = 0);
    void reconnect(shs::t::shs_time_t reconnecting_timeout = 0);

    void setConnectingTimeout(const shs::t::shs_time_t timeout) { m_connecting_timeout = timeout; }
    void setReconnectingTimeout(const shs::t::shs_time_t timeout) { m_reconnecting_timeout = timeout; }
    shs::t::shs_time_t getConnectingTimeout() const { return m_connecting_timeout; }
    shs::t::shs_time_t getReconnectingTimeout() const { return m_reconnecting_timeout; }

    shs::t::shs_IP_t getIP() const { return m_hostIP; }
    shs::t::shs_port_t getPort() const { return m_port; }

    void setActive(const bool flag);
    bool connected() { return client.connected(); }
    shs::TcpSocket::Status getStatus() const { return m_status; }

    // -------------------- shs::Process (from shs::DTPbus) --------------------
    void start() override;
    void tick() override;
    void stop() override { if (client.connected()) client.stop(); m_status = Status::DISCONNECTED; }

    // -------------------- shs::DTPbus ----------------------------------------
    bool isActive() const override { return m_status != Status::INACTIVE; }

    shs::DTPbus::Status checkBus() override { return shs::DTPbus::checkBus(client); }

    uint8_t sendPacket(const shs::DTPpacket& packet) override { return shs::DTPbus::sendPacket(client, packet); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return shs::DTPbus::sendRAW(client, bc); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return shs::DTPbus::sendRAW(client, it); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return shs::DTPbus::sendRAW(client, data, size); }

private:
    shs::t::shs_IP_t m_hostIP;
    shs::t::shs_port_t m_port{};
    shs::TcpSocket::Status m_status;

    shs::ProgramTime m_timer;

    shs::t::shs_time_t m_connecting_timeout = 2000;
    shs::t::shs_time_t m_reconnecting_timeout = 5000;

    std::function<void(shs::TcpSocket& client)> m_connect_callback;
    std::function<void(shs::TcpSocket& client)> m_disconnect_callback;

};


#endif    // #if defined(SHS_SF_NETWORK)
