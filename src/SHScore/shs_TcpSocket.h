#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
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
#include "../SHSqt_core/shs_qt_TcpSocket.h"
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
        { auto packet = shs::DTP_APIpackets::getInitialPacket(socket.busID); socket.client.write(packet.bc.getPtr(), packet.bc.size()); })

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
        m_hostIP(hostIP), m_port(port),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}


    explicit TcpSocket
    (
    #ifdef SHS_SF_ARDUINO
        const WiFiClient& other,
    #elif defined(SHS_SF_QT)
       // QObject* parent,
    #endif
        const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
        const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
        const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
    )
        :
        DTPbus(busID, handler, bufsize),
        client(), m_port(0),
        m_connect_callback(connect_callback), m_disconnect_callback(disconnect_callback)
    {}

    virtual ~TcpSocket() = default;

    // native functions

    void reconnect() { m_connect(); }

    shs::t::shs_IP_t getIP() const { return m_hostIP; }
    shs::t::shs_port_t getPort() const { return m_port; }


    // inherited from shs::Process (from shs::DTPbus)
    void start() override { client.connect(m_hostIP, m_port); }
    void tick() override { if (!client.connected() && m_disconnect_callback) m_disconnect_callback(*this); }
    void stop() override { client.stop(); }


    // inherited from shs::DTPbus
    Status checkBus() override { return shs::DTPbus::checkBus(client); }

    uint8_t sendPacket(const shs::DTPpacket& packet) override { return shs::DTPbus::sendPacket(client, packet); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return shs::DTPbus::sendRAW(client, bc); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return shs::DTPbus::sendRAW(client, it); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return shs::DTPbus::sendRAW(client, data, size); }


private:
    shs::t::shs_IP_t m_hostIP;
    shs::t::shs_port_t m_port;

    std::function<void(shs::TcpSocket& client)> m_connect_callback;
    std::function<void(shs::TcpSocket& client)> m_disconnect_callback;

    void m_connect() { if (client.connect(m_hostIP, m_port) && m_connect_callback) m_connect_callback(*this); }
};
