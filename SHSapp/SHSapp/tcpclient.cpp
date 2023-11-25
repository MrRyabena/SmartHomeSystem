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

    for (;;) {
        if (socket->bytesAvailable()) {
            qDebug() << "available!";
            lastPacketTime = time;
            if (!meslen) socket->read((char*)&meslen, 1);
            qDebug() << (int)meslen;
            if (socket->bytesAvailable() < (int)meslen - 1) break;

            shs::ByteCollector col(meslen);

            col.add(meslen);
            socket->read((char*)&col.buf[1], col.buf[0]);
            col.ptr += col.buf[0] - 1;
            meslen = 0;
            qDebug() << "Message";
            for (auto i = 0; i < col.size(); i++) qDebug() << col.buf[i];
            uint16_t crc = shs::crc_8(col.buf, col.buf[0] - 1);
            qDebug() << "crc: " << crc << "==" << col.buf[col.buf[0] - 1];
            qDebug() << "dtp";


            qDebug() << dtp->parseDTP(&col, parseData);

        }
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


void parseData(shs::DTPdata &stc, shs::ByteCollector *data) {
    qDebug() << "parse...";
    switch (data->readPtr[0]) {

    default:
        shs::ByteCollector col(1);
        col.add(shs::DTPcommands::answer, 1);
        qDebug() << "from: " << stc.from << "\nto: " << stc.to << "\ndatasize: " << stc.datasize;
        for (auto i = 0; i < data->size(); i++) qDebug() << static_cast<char>(data->buf[i]);
        //sendPacket(&col, 104);
        break;
    }
}
