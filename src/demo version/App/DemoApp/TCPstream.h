#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QDateTime>
#include <stdint.h>

#include "../../../SHScore/SHSByteCollector.h"
#include "../../../SHScore/SHSdtp.h"
#include "../../../SHScore/SHSsettings_private.h"
#include "../../../SHScore/SHSStream.h"

#include "../../../SHScore/SHSdtp.h"

#include "../../../SHScore/SHSCRC.h"
#include "../../../SHScore/SHSCallbacksKeeper.h"
#include "../../../SHScore/SHSsettings_private.h"


const char* ip = "192.168.1.4";
int port = 50000;
const shs::settings::shs_ModuleID_t ID = 10;


class TCPstream : public shs::Stream
{
public:
    TCPstream(QTcpSocket* tcp) : m_tcp(tcp) {}

    uint8_t write(const uint8_t *buf, size_t size) {     return m_tcp->write((char*)buf, size);    }
    uint8_t read() {
        char a;
        qint64 size = 1;
        m_tcp->read(&a, size);
        return static_cast<uint8_t>(a);
    }
    uint8_t available(){return m_tcp->bytesAvailable();}

private:
    QTcpSocket *m_tcp{};

};

void dtpSetup() {
    QTcpSocket socket;
    socket.connectToHost(ip, port);

    if (socket.waitForConnected(500)) {
        qDebug() << "TCP connected!";

    }
    else qDebug() << "TCP no connected";

    TCPstream stream(&socket);
    shs::DTP dtp(&stream, ID);

    qDebug() << dtp.tick();
}

#endif // TCPCLIENT_H
