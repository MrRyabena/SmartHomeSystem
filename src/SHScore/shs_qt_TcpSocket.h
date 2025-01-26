#pragma once

#include "shs_settings_private.h"
#include "shs_types.h"

#ifndef SHS_SF_QT
#error "The class only supports the Qt platform"
#endif


#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

#include <stdint.h>


namespace shs
{
    namespace qt
    {
        class TcpSocket;
    }
};


class shs::qt::TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject* parent = nullptr);

    ~TcpSocket() = default;


    uint8_t write(const uint8_t* buf, const uint16_t size) { qDebug() << "sending data"; return m_socket.write(reinterpret_cast<const char*>(buf), size); }
    uint8_t read() { char data{}; m_socket.read(&data, 1); return data; }
    uint8_t read(uint8_t* buf, const uint16_t size) { return m_socket.read(reinterpret_cast<char*>(buf), size); }
    uint8_t available() { return m_socket.bytesAvailable(); }

    bool connectToHost(const shs::t::shs_IP_t ip, const shs::t::shs_port_t port)
    {
        m_socket.connectToHost(QHostAddress(ip), port);
        qDebug() << m_socket.isOpen() << ' ' << m_socket.isWritable() << ' ' << m_socket.localAddress().toString();
        if (m_socket.waitForConnected(3000))
        {
            qDebug() << "connected";
            return true;
        }
        return false;
    }

    void disconnectFromHost() { m_socket.disconnectFromHost(); }
    void stop() { disconnect(); }
    bool connected() { return m_socket.isOpen(); }

signals:
    void s_connected();
    void disconnected();
    void errorOccurred(const QString& errorString);
    void dataReceived();

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onReadyRead();

private:
    QTcpSocket m_socket;
};
