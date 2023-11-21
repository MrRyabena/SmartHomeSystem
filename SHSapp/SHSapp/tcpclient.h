#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QDateTime>
#include <stdint.h>
#include "../../SHSlibrary/ByteCollector.h"
#include "../../SHSlibrary/SHSdtp.h"
#include "../../SHSlibrary/SHSalgoritm.h"


extern void parseData(shs::DTPdata &stc, shs::ByteCollector *data);


class TCPclient : public QObject
{
    Q_OBJECT
public:
    explicit TCPclient(QObject *parent = 0);

    ~TCPclient();

    void begin(uint8_t ID, const char *ip, int port);
    void connect(const char *ip, int port);
    void sendPacket(shs::ByteCollector *packet, uint8_t to);


    void checkData();
    void checkConnection();

    uint8_t ID{};
    const char * IP{};
    int Port{};
public slots:
    void process();

private:
    QTcpSocket *socket;
    shs::DTP *dtp;
    unsigned long long lastPacketTime{};
    uint8_t meslen{};
};

#endif // TCPCLIENT_H
