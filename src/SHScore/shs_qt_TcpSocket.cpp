#include "shs_qt_TcpSocket.h"

#ifdef SHS_SF_QT

#define SHS_SF_DEBUG
#include "shs_debug.h"

shs::qt::TcpSocket::TcpSocket(QObject* parent)
    : QObject(parent), m_qtcp_socket(new QTcpSocket(this))
{
    connect(m_qtcp_socket, &QTcpSocket::connected, this, &TcpSocket::onConnected);
    connect(m_qtcp_socket, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
    connect(m_qtcp_socket, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpSocket::onError);
    connect(m_qtcp_socket, &QTcpSocket::readyRead, this, &TcpSocket::onReadyRead);
}


void shs::qt::TcpSocket::onConnected()
{
    doutln("QTcpSocket connected");

    m_connected = true;
    dout("connected: "); doutln(connected());
    emit s_connected();

}


void shs::qt::TcpSocket::onDisconnected()
{
    doutln("QTcpSocket disconnected");

    m_connected = false;
    dout("connected: "); doutln(connected())
    emit disconnected();
}


void shs::qt::TcpSocket::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << m_qtcp_socket->errorString();
    emit errorOccurred(m_qtcp_socket->errorString());
}


void shs::qt::TcpSocket::onReadyRead()
{
    emit dataReceived();
}

#endif  // #ifdef SHS_SF_QT
