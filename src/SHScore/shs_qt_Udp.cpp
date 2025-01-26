#include "shs_qt_Udp.h"

shs::qt::UdpSocket::UdpSocket(QObject* parent) : QObject(parent), m_socket(this)
{
    connect(&m_socket, static_cast<void(QUdpSocket::*)(QAbstractSocket::SocketError)>(&QUdpSocket::error), this, &UdpSocket::onError);
    connect(&m_socket, &QUdpSocket::readyRead, this, &UdpSocket::onReadyRead);
}


void shs::qt::UdpSocket::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << "-" << m_socket.errorString();
    emit error(m_socket.errorString());
}

