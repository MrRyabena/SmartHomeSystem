#pragma once

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "SHSByteCollector.h"
#include "SHSdtp.h"

namespace shs
{
    class TcpServer;
};

class shs::TcpServer
{
public:
    WiFiServer *server;
    WiFiClient *clients;
    shs::DTP *dtp;

    const uint8_t *IP{};
    uint8_t maxClients{};

    TcpServer(const uint8_t *IPaddress, void (*TCPhandle)(shs::DTPdata &), uint16_t port = 50000, uint8_t max_clients = 6);
    ~TcpServer();

    void begin();
    void tick();

    uint8_t sendPacket(shs::ByteCollector *col, uint8_t id);
    void sendRAW(uint8_t *buf, uint8_t size);

private:
    void (*_TCPhandle)(shs::DTPdata &){};
    uint8_t *lens{};
    uint8_t i{};
};
