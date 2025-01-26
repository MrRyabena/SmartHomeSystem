#include "shs_qt_TcpSocket.h"


shs::qt::TcpSocket::TcpSocket(QObject* parent)
    : QObject(parent), m_socket(this)
{
    connect(&m_socket, &QTcpSocket::connected, this, &TcpSocket::onConnected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
    connect(&m_socket, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpSocket::onError);
    connect(&m_socket, &QTcpSocket::readyRead, this, &TcpSocket::onReadyRead);
}


void shs::qt::TcpSocket::onConnected()
{
    emit s_connected();
}


void shs::qt::TcpSocket::onDisconnected()
{
    emit disconnected();
}


void shs::qt::TcpSocket::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << "-" << m_socket.errorString();
    emit errorOccurred(m_socket.errorString());
}


void shs::qt::TcpSocket::onReadyRead()
{
    emit dataReceived();
}

