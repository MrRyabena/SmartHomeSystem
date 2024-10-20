#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <stdint.h>

#include "shs_ByteCollector.h"
#include "shs_DTP.h"



//extern void parseData(shs::DTPdata &stc);


//class TCPclient : public QObject
//{
//    Q_OBJECT
//public:
//    explicit TCPclient(QObject *parent = 0);

//    ~TCPclient();

//    void begin(uint8_t ID, const char *ip, int port);
//    void connect(const char *ip, int port);
//    void sendPacket(shs::ByteCollector *packet, uint8_t to);


//    void checkData();
//    void checkConnection();

//    uint8_t ID{};
//    const char * IP{};
//    int Port{};


//private:
//    QTcpSocket *socket;
//    shs::DTP *dtp;
//    unsigned long long lastPacketTime{};
//    uint8_t meslen{};
//};

//#endif // TCPCLIENT_H
