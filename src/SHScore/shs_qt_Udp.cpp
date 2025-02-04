#include "shs_qt_Udp.h"

#ifndef SHS_SF_DISABLE_QT

shs::qt::UdpSocket::UdpSocket(QObject* parent) : QObject(parent), m_socket(new QUdpSocket(this))
{
    connect(m_socket, static_cast<void(QUdpSocket::*)(QAbstractSocket::SocketError)>(&QUdpSocket::error), this, &UdpSocket::onError);
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpSocket::onReadyRead);
}


void shs::qt::UdpSocket::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << "-" << m_socket->errorString();
    emit error(m_socket->errorString());
}


void shs::qt::UdpSocket::processDatagrams()
{
    m_buf.shrink_to_read();
    do
    {
        auto size = m_socket->pendingDatagramSize();
        m_buf.reserve(size);
        m_socket->readDatagram(reinterpret_cast<char*>(m_buf.getPtr() + m_buf.getPositionBack()), size);
        m_buf.setPositionBack(m_buf.getPositionBack() + size);

    } while (m_socket->hasPendingDatagrams());

}

#endif  // #ifndef SHS_SF_DISABLE_QT
