#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>
#include <stdint.h>
#include <QThread>
#include "mainwindow.h"

#include "../../../SHScore/SHSByteCollector.h"
#include "../../../SHScore/SHSStream.h"
#include "../../../SHScore/SHSdtp.h"
#include "../../../SHScore/SHSCallbacksKeeper.h"
#include "../../../SHScore/SHSsettings_private.h"
#include "../../../SHScore/SHSAPI.h"
#include "../../config/config_api.h"


inline const char* ip = "192.168.1.4";
inline int port = 50000;
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

class Api : public shs::API {
public:
    explicit Api(MainWindow *w, const shs::settings::shs_ID_t apiID = 10, const shs::settings::shs_ID_t to = 4) : ::shs::API(apiID, to), m_w(w) {}

    uint8_t handler(shs::ByteCollector &data) override;

protected:
    MainWindow *m_w;

};

class qDTP : public QThread
{
public:
    shs::DTP dtp;
    QTcpSocket socket;
    TCPstream stream;
    Api api;

    qDTP(MainWindow *w) : socket(), stream(&socket), dtp(&stream, ID), api(w) {}

    void setup() {


    socket.connectToHost(ip, port);

    if (socket.waitForConnected(500)) {
        qDebug() << "TCP connected!";
    }
    else qDebug() << "TCP no connected";

    dtp.attach(&api);

    qDebug() << dtp.tick();

}

void run() override {
    for (;;) {
       qDebug() << dtp.tick();
    }
}

};

#endif // TCPCLIENT_H
