#include "shs_TcpSocket.h"

#if defined(SHS_SF_NETWORK)

std::function<void(shs::TcpSocket&)> shs::TcpSocket::default_connect_callback =
[](shs::TcpSocket& socket) { if (socket.isActive()) socket.sendPacket(shs::DTP_APIpackets::getInitialPacket(socket.busID)); };

std::function<void(shs::TcpSocket&)> shs::TcpSocket::default_disconnect_callback =
[](shs::TcpSocket& socket) { if (socket.isActive()) socket.reconnect(); };

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
{}


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
    if (connected()) m_status = Status::CONNECTED;
}


void shs::TcpSocket::connect(shs::t::shs_time_t connecting_timeout)
{
    if (!isActive()) return;
    if (connected())
    {
        m_status = Status::CONNECTED;
        return;
    }

    if (connecting_timeout) m_connecting_timeout = connecting_timeout;
    if (m_connecting_timeout == 0)  return;
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
    if (reconnecting_timeout) m_reconnecting_timeout = reconnecting_timeout;
    if (m_reconnecting_timeout == 0)
    {
        stop();
        m_status = Status::DISCONNECTED;
        return;
    }

    m_timer.reset();
    m_status = Status::RECONNECTING;
    client.stop();

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
    if (connected())
    {
        m_status = Status::CONNECTED;
        return;
    }
    connect();
}


void shs::TcpSocket::tick()
{
    switch (m_status)
    {
        case Status::DISCONNECTED:
            if (connected()) m_status = Status::CONNECTED;
            if (m_timer.milliseconds() < m_connecting_timeout) connect();
            break;

        case Status::CONNECTING:
            if (connected())
            {
                m_timer.reset();
                m_status = Status::CONNECTED;
                if (m_connect_callback) m_connect_callback(*this);

            }
            if (m_timer.milliseconds() > m_connecting_timeout)
            {
                reconnect();
            }
            break;

        case Status::RECONNECTING:
            if (connected())
            {
                m_timer.reset();
                m_status = Status::CONNECTED;

            }
            else if (m_timer.milliseconds() > m_reconnecting_timeout)
            {
                stop();
            }
            else
            {
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
            break;

        case Status::CONNECTED:
            if (!connected())
            {
                m_status = Status::DISCONNECTED;
                if (m_disconnect_callback)m_disconnect_callback(*this);
            }
            break;

        case Status::INACTIVE: break;
        default: break;
    }

}


#endif  // defined(SHS_SF_NETWORK)
