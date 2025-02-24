#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
    v2.0.0 — updated functionality, debugged, tested.
      - It is based on shs::DTPbus.
      - Automatic reconnection in case of loss of connection.
      - Qt support.
*/


#include <stdint.h>
#include <functional>

#include "shs_settings_private.h"

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


#define default_connect_callback ([](shs::TcpSocket& socket) \
        { socket.sendPacket(shs::DTP_APIpackets::getInitialPacket(socket.busID)); })

#define default_disconnect_callback ([](shs::TcpSocket& socket) { socket.reconnect(); })


    explicit TcpSocket
    (
        const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
        const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
    )
        :
        DTPbus(busID, handler, bufsize),
        m_hostIP(hostIP), m_port(port), m_active_flag(true),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}


    explicit TcpSocket
    (
    #ifdef SHS_SF_ARDUINO
        const WiFiClient& parent,
    #elif defined(SHS_SF_QT)
        QObject* parent,
        const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
    #endif
        const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
    )
        :
        DTPbus(busID, handler, bufsize),
    #ifdef SHS_SF_QT
        m_hostIP(hostIP), m_port(port),
    #endif
        client(parent), m_active_flag(true),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}

    ~TcpSocket() = default;


    // -------------------- native functions -----------------------------------

    void reconnect() { m_connect(); }

    shs::t::shs_IP_t getIP() const { return m_hostIP; }
    shs::t::shs_port_t getPort() const { return m_port; }

    void setActive(const bool flag) { m_active_flag = flag; }


    // -------------------- shs::Process (from shs::DTPbus) --------------------
    void start() override { m_connect(); }
    void tick() override { if (!client.connected() && m_disconnect_callback) m_disconnect_callback(*this); }
    void stop() override { client.stop(); }


    // -------------------- shs::DTPbus ----------------------------------------
    bool isActive() const override { return m_active_flag; }

    Status checkBus() override { return shs::DTPbus::checkBus(client); }

    uint8_t sendPacket(const shs::DTPpacket& packet) override { return shs::DTPbus::sendPacket(client, packet); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return shs::DTPbus::sendRAW(client, bc); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return shs::DTPbus::sendRAW(client, it); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return shs::DTPbus::sendRAW(client, data, size); }


private:
    shs::t::shs_IP_t m_hostIP;
    shs::t::shs_port_t m_port{};
    bool m_active_flag;

    std::function<void(shs::TcpSocket& client)> m_connect_callback;
    std::function<void(shs::TcpSocket& client)> m_disconnect_callback;


    void m_connect()
    {
        if (
        #ifdef SHS_SF_ARDUINO
            client.connect(m_hostIP, m_port)
        #elif defined(SHS_SF_QT)
            client.connectToHost(m_hostIP, m_port)
        #endif
            && m_connect_callback)
        {
            m_connect_callback(*this);
        }
    }
};
