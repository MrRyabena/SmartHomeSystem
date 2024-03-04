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

#include "../../SHSsettings/SHSsettings.h"

#include <cmath>

inline const char* ip = "192.168.1.4";
inline int port = 50000;
const shs::settings::shs_ModuleID_t ID = 10;

#define RESIST_BASE 10000   // сопротивление при TEMP_BASE градусах по Цельсию (Ом)
#define TEMP_BASE 25        // температура, при которой измерено RESIST_BASE (градусов Цельсия)
#define B_COEF 3435         // бета коэффициент термистора (3000-4000)

class TCPstream : public shs::Stream
{
public:
    TCPstream(QTcpSocket* tcp) : m_tcp(tcp) {}

    uint8_t write(const uint8_t *buf, uint16_t size) override {     return m_tcp->write((char*)buf, size);    }
    uint8_t read() override {
        char a;
        qint64 size = 1;
        m_tcp->read(&a, size);
        return static_cast<uint8_t>(a);
    }
    uint8_t available() override {return m_tcp->bytesAvailable();}

private:
    QTcpSocket *m_tcp{};

};

class Api : public shs::API {
public:
    explicit Api(MainWindow *w, const shs::settings::shs_ID_t apiID = 10, const shs::settings::shs_ID_t to = 4) : ::shs::API(apiID, to), m_w(w) {}

    uint8_t handler(shs::ByteCollector &data) override;
    double getThermTemp(int resistance) {
      double thermistor;
      thermistor = 10000 / ((double)1023 / resistance - 1);
      thermistor /= RESIST_BASE;                        // (R/Ro)
      thermistor = std::log(thermistor) / B_COEF;            // 1/B * ln(R/Ro)
      thermistor += (double)1.0 / (TEMP_BASE + 273.15);  // + (1/To)
      thermistor = (double)1.0 / thermistor - 273.15;    // инвертируем и конвертируем в градусы по Цельсию
      return thermistor;
    }

protected:
    MainWindow *m_w;

};

class qDTP
{
public:
    shs::DTP dtp;

    TCPstream stream;
    Api api;
    QTcpSocket *socket;

    qDTP(MainWindow *w, QTcpSocket *_socket) : socket(_socket), stream(_socket), dtp(&stream, ID), api(w) {}

    void setup() {


    socket->connectToHost(ip, port);

    if (socket->waitForConnected(500)) {
        qDebug() << "TCP connected!";
    }
    else qDebug() << "TCP no connected";

    dtp.attach(&api);

    qDebug() << dtp.tick();
    shs::ByteCollector bc(2);
    bc.add(15);

    dtp.sendPacket(&bc, 4, -10, 10);

}

void tick() {
            dtp.tick();
    }

private:
time_t time = 0;


};

#endif // TCPCLIENT_H
