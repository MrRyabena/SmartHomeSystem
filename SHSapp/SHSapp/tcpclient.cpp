#include "tcpclient.h"



TCPclient::TCPclient(QObject *parent) :
    QObject(parent)
{

}


TCPclient::~TCPclient() {
    delete dtp;
}


void TCPclient::begin(uint8_t id, const char* ip, int port) {
    dtp = new shs::DTP(id);
    ID = id;
    IP = ip;
    Port = port;
}


void TCPclient::connect(const char *ip, int port) {
    socket = new QTcpSocket(this);
    socket->connectToHost(ip, port);

    if (socket->waitForConnected(5000)) {
        qDebug() << "TCP connected!";

    }
    else qDebug() << "TCP no connected";
}

void TCPclient::sendPacket(shs::ByteCollector *packet, uint8_t to) {
    dtp->packDTP(packet, to);
    socket->write((const char*)packet->buf, packet->size());
    socket->waitForBytesWritten(1000);
    if (socket->state() == QTcpSocket::ConnectedState) lastPacketTime = QDateTime::currentDateTime().toTime_t();
    else {
        checkConnection();
    }
}

void TCPclient::checkData() {
    unsigned long long time = QDateTime::currentDateTime().toTime_t();

    socket->waitForReadyRead(3000);
    if (socket->bytesAvailable()) {
        lastPacketTime = time;
        shs::ByteCollector col(1);
        socket->read((char*)col.buf, 1);
        col.reserve(col.buf[0]);
        socket->read((char*)col.buf, col.buf[0]);
        col.ptr += col.buf[0];

        dtp->parceDTP(col, )


                return;
    }
    if (lastPacketTime - time >= 60) {
        checkConnection();
    }
}


void TCPclient::checkConnection() {
    shs::ByteCollector col(1);
    col.add(254, 1);
    dtp->packDTP(&col, 0);
    socket->write((const char*)col.buf, col.size());
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);
    if(socket->bytesAvailable() && socket->state() == QTcpSocket::ConnectedState);
    else {
        socket->close();
        socket->connectToHost(IP, Port);
    }
    lastPacketTime = QDateTime::currentDateTime().toTime_t();
}


void TCPclient::parseData(shs::DTPdata &stc, shs::ByteCollector *data) {
    switch (data->readPtr[0]) {

    default:
        shs::ByteCollector col(1);
        col.add(shs::DTPcommands::answer, 1);
        sendPacket(&col, 104);
        break;
    }
}
