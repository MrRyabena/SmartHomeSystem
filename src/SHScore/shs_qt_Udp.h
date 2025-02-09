#pragma once

#include "shs_settings_private.h"

#ifdef SHS_SF_QT

#include "shs_types.h"
#include "shs_ByteCollector.h"

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>


#include <stdint.h> 


namespace shs
{
    namespace qt
    {
        class UdpSocket;
    }
}


class shs::qt::UdpSocket : public QObject
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject* parent = nullptr);
    ~UdpSocket() = default;

    void begin(const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { m_socket->bind(QHostAddress::Any, port); }
    void stop() { m_socket->close(); }

    uint8_t write(const uint8_t* buf, const uint16_t size, const shs::t::shs_IP_t ip, const shs::t::shs_port_t port) { return m_socket->writeDatagram(reinterpret_cast<const char*>(buf), size, QHostAddress(static_cast<uint32_t>(ip)), port); }
    uint8_t read() { uint8_t value{}; read(&value, 1); return value; }
    uint8_t read(uint8_t* buf, const uint16_t size) { m_buf.read(buf, size); return size; }
    uint8_t available() { return m_buf.readAvailable(); }

    void processDatagrams();

    bool joinMulticastGroup(const shs::t::shs_IP_t groupIP) { return m_socket->joinMulticastGroup(QHostAddress(static_cast<uint32_t>(groupIP))); }
    bool leaveMulticastGroup(const shs::t::shs_IP_t groupIP) { return m_socket->leaveMulticastGroup(QHostAddress(static_cast<uint32_t>(groupIP))); }

    QUdpSocket* getQUdpPtr() const { return m_socket; }

signals:
    void dataReceived();
    void error(const QString& errorString);

private slots:
    void onReadyRead() { processDatagrams(); emit dataReceived(); }
    void onError(QAbstractSocket::SocketError socketError);

private:
    QUdpSocket* m_socket;
    shs::ByteCollector<> m_buf;
};

#endif  // #ifdef SHS_SF_QT
