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
    class TcpClient;
};

class shs::TcpClient
{
public:
    WiFiClient client{};
    shs::DTP *dtp{};

    const uint8_t *IP{};
    uint16_t port{};

    TcpClient(const uint8_t *IPaddress, void (*TCPhandle)(shs::DTPdata &), uint16_t _port = 50000);
    ~TcpClient();

    void begin();
    void tick();
    uint8_t sendPacket(shs::ByteCollector *col, uint8_t id);
    void sendRAW(uint8_t *buf, uint8_t size);

private:
    void (*_TCPhandle)(shs::DTPdata &){};
    uint8_t len{};
};
