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
    doutln("TcpSocket::connect");
    if (!isActive()) return;

    if (connecting_timeout) m_connecting_timeout = connecting_timeout;

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
        m_timer.reset();
        m_status = Status::CONNECTED;
        if (m_connect_callback) m_connect_callback(*this);
    }

}

void shs::TcpSocket::reconnect(const shs::t::shs_time_t reconnecting_timeout)
{
    doutln("TcpSocket::reconnect");
    if (reconnecting_timeout) m_reconnecting_timeout = reconnecting_timeout;
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
    connect();
}


void shs::TcpSocket::tick()
{
    switch (m_status)
    {
        case Status::DISCONNECTED:
            {
                doutln("disconnected...");
                if (m_timer.milliseconds() < m_connecting_timeout) connect();
            }
            break;
        case Status::CONNECTING:
            {
                doutln("connecting...");
                if (connected())
                {
                    m_timer.reset();
                    m_status = Status::CONNECTED;
                    if (m_connect_callback) m_connect_callback(*this);
                    doutln("connected!");
                }
                if (m_timer.milliseconds() > m_connecting_timeout)
                {
                    doutln("connection timeout, reconnecting...");
                    reconnect();
                }
            }
            break;

        case Status::RECONNECTING:
            {
                doutln("reconnecting...");
                if (connected())
                {
                    m_timer.reset();
                    m_status = Status::CONNECTED;
                    doutln("reconnected!");
                }
                if (m_timer.milliseconds() > m_reconnecting_timeout)
                {
                    m_timer.reset();
                    m_status = Status::DISCONNECTED;
                    client.stop();
                    doutln("reconnection timeout, disconnected");
                }
            }
            break;

        case Status::CONNECTED:
            {
                // if (checkBus() == shs::DTPbus::packet_received || status == shs::DTPbus::packet_processed)
                // {
                //     doutln("data received from TcpSocket");
                // }

                if (!connected())
                {
                    m_status = Status::DISCONNECTED;
                    if (m_disconnect_callback) m_disconnect_callback(*this);
                }
            }
            break;

        case Status::INACTIVE: [[fallthrough]];
        default: break;
    }

}


