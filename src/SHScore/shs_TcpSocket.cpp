#include "shs_TcpSocket.h"
#define SHS_SF_DEBUG
#include "shs_debug.h"

std::function<void(shs::TcpSocket&)> shs::TcpSocket::default_connect_callback =
[](shs::TcpSocket& socket) { doutln("connected callback: send packet");  if (socket.isActive()) socket.sendPacket(shs::DTP_APIpackets::getInitialPacket(socket.busID)); };

std::function<void(shs::TcpSocket&)> shs::TcpSocket::default_disconnect_callback =
[](shs::TcpSocket& socket) { doutln("disconnected callback"); if (socket.isActive()) socket.reconnect(); };

shs::TcpSocket::TcpSocket(
    const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
    const shs::t::shs_busID_t busID, shs::API* handler, const uint8_t bufsize,
    const std::function<void(shs::TcpSocket&)>& connect_callback,
    const std::function<void(shs::TcpSocket&)>& disconnect_callback
)
    : DTPbus(busID, handler, bufsize),
    m_hostIP(hostIP), m_port(port),
    m_connect_callback(connect_callback),
    m_disconnect_callback(disconnect_callback)
{
    doutln("TcpSocket::TcpSocket");
}



shs::TcpSocket::TcpSocket(
#ifdef SHS_SF_ARDUINO
    const WiFiClient& parent,
#elif defined(SHS_SF_QT)
    QObject* parent,
    const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
#endif
    const shs::t::shs_busID_t busID, shs::API* handler,
    const uint8_t bufsize, const std::function<void(shs::TcpSocket&)>& connect_callback,
    const std::function<void(shs::TcpSocket&)>& disconnect_callback)
    : DTPbus(busID, handler, bufsize),
#ifdef SHS_SF_QT
    m_hostIP(hostIP), m_port(port),
#endif
    client(parent),
    m_connect_callback(connect_callback),
    m_disconnect_callback(disconnect_callback)
{
    doutln("TcpSocket::TcpSocket from parent");
}

void shs::TcpSocket::connect(shs::t::shs_time_t connecting_timeout)
{
    dout("TcpSocket::connect:  ");
    if (!isActive()) { doutln("inactive"); return; }
    if (connected())
    {
        doutln("already connected");
        m_status = Status::CONNECTED;
        return;
    }

    if (connecting_timeout) m_connecting_timeout = connecting_timeout;
    if (m_connecting_timeout == 0) { doutln("connecting timeout = 0"); return; }
    m_timer.reset();
    m_status = Status::CONNECTING;

    bool connected = false;
#ifdef SHS_SF_ARDUINO
    connected = client.connect(m_hostIP, m_port);
#elif defined(SHS_SF_QT)
    connected = client.connectToHost(m_hostIP, m_port);
#endif

    if (connected)
    {
        doutln("connected immediately");
        m_timer.reset();
        m_status = Status::CONNECTED;
        if (m_connect_callback) m_connect_callback(*this);
    }
    else
    {
        doutln("connecting...");
    }


}

void shs::TcpSocket::reconnect(const shs::t::shs_time_t reconnecting_timeout)
{
    doutln("TcpSocket::reconnect");
    if (reconnecting_timeout) m_reconnecting_timeout = reconnecting_timeout;
    if (m_reconnecting_timeout == 0)
    {
        stop();
        m_status = Status::DISCONNECTED;
        return;
    }

    m_timer.reset();
    m_status = Status::RECONNECTING;
}


void shs::TcpSocket::setActive(const bool flag)
{
    if (flag && !isActive())
    {
        start();
    }
    else if (!flag && isActive())
    {
        stop();
        m_status = Status::INACTIVE;
    }
}


void shs::TcpSocket::start()
{
    dout("TcpSocket::start:  ");
    if (connected())
    {
        m_status = Status::CONNECTED;
        doutln("already connected");
        return;
    }
    connect();
}


void shs::TcpSocket::tick()
{
    // dout();

    //if (!connected() && m_disconnect_callback) m_disconnect_callback(*this);

    // if (!connected())
    // {
    //     if (m_status == Status::CONNECTED)
    //     {
    //         m_status = Status::DISCONNECTED;
    //         doutln("TcpSocket::tick:  Status::DISCONNECTED: client disconnected");
    //         if (m_disconnect_callback)
    //         {
    //             m_disconnect_callback(*this);
    //             return;
    //         }
    //     }
    //     else if (m_status == Status::DI)
    // }

    // switch (m_status)
    // {
    //     case Status::DISCONNECTED:
    //         {
    //             dout("TcpSocket::tick:  Status::DISCONNECTED:  ");
    //             if (connected())
    //             {
    //                 doutln("error: connected while disconnected");
    //                 m_status = Status::CONNECTED;
    //                 return;
    //             }

    //             // if (m_timer.milliseconds() < m_connecting_timeout)
    //             // {
    //             //     doutln("call connect()");
    //             //     connect();
    //             //     return;
    //             // }
    //             // else
    //             // {
    //             //     doutln("disconnected");
    //             // }
    //         }
    //         break;
    //     case Status::CONNECTING:
    //         {
    //             dout("TcpSocket::tick:  Status::CONNECTING:  ");
    //             if (connected())
    //             {
    //                 m_timer.reset();
    //                 m_status = Status::CONNECTED;
    //                 if (m_connect_callback) m_connect_callback(*this);
    //                 doutln("connected!");
    //                 return;
    //             }
    //             // if (m_timer.milliseconds() > m_connecting_timeout)
    //             // {
    //             //     doutln("connection timeout, reconnecting...");
    //             //     reconnect();
    //             //     return;
    //             // }
    //         }
    //         break;

    //     case Status::RECONNECTING:
    //         {
    //             dout("TcpSocket::tick:  Status::RECONNECTING:  ");
    //             // if (connected())
    //             // {
    //             //     m_timer.reset();
    //             //     m_status = Status::CONNECTED;
    //             //     doutln("reconnected!");
    //             //     return;
    //             // }
    //             // if (m_timer.milliseconds() > m_reconnecting_timeout)
    //             // {
    //             //     stop();
    //             //     doutln("reconnection timeout, disconnected");
    //             //     return;
    //             // }
    //         }
    //         break;

    //     case Status::CONNECTED:
    //         {
    //             doutln("TcpSocket::tick:  Status::CONNECTED");
    //             if (!client.connected())//!connected())
    //             {
    //                 m_status = Status::DISCONNECTED;
    //                 doutln("TcpSocket::tick:  Status::DISCONNECTED: client disconnected");
    //                 if (m_disconnect_callback)
    //                 {
    //                     m_disconnect_callback(*this);
    //                     return;
    //                 }

    //                 return;
    //             }
    //         }
    //         break;

    //     case Status::INACTIVE: break;
    //     default: break;
    // }

}


