#pragma once

#include "shs_settings_private.h"
#include "shs_types.h"

#ifndef SHS_SF_QT
#error "The class only supports the Qt platform"
#endif


#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>

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

    void begin(const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT) { m_socket.bind(port); }
    void stop() { m_socket.close(); }

    uint8_t write(const uint8_t* buf, const uint16_t size, const shs::t::shs_IP_t ip, const shs::t::shs_port_t port) { return m_socket.writedatagram(reinterpret_cast<const char*>(buf), size, QHostAddress(static_cast<uint32_t>(ip), port); ) }
    uint8_t read(uint8_t* buf, const uint16_t size) { return m_socket.readDatagram(reinterpret_cast<char*>(buf), size); }
    uint8_t available() { return m_socket.pendingDatagramSize(); }

    bool joinMulticastGroup(const shs::t::shs_IP_t groupIP) { m_socket.joinMulticastGroup(static_cast<uint32_t>(groupIP)); }
    bool leaveMulticastGroup(const shs::t::shs_IP_t groupIP) { m_socket.leaveMulticastGroup(static_cast<uint32_t>(groupIP)); }

signals:
    void dataReceived(const QByteArray& data);
    void error(const QString& errorString);

private slots:
    void onReadyRead() { emit dataReceived(); }
    void onError(QAbstractSocket::SocketError socketError);

private:
    QUdpSocket m_socket;
};
