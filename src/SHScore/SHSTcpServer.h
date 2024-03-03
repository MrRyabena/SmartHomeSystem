#pragma once
/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — corrected.
    v1.0.0 — release.
*/

/*
  The server class for processing clients.
  Need to be finalized.
*/
#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <WiFiServer.h>
#include <WiFiClient.h>

#include "SHSByteCollector.h"
#include "SHSdtp.h"
#include "SHSsettings_private.h"

namespace shs
{
    class TcpServer;
};

class shs::TcpServer
{
public:
    WiFiServer server;
    WiFiClient *clients;
    shs::DTP *dtp{};

    const uint8_t *IP{};
    uint8_t maxClients{};

    TcpServer(const uint8_t *IPaddress, uint16_t port = 50000, uint8_t max_clients = 6);
    ~TcpServer();

    void begin();
    void tick();

    uint8_t sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to,
                             const shs::settings::shs_ID_t api_ID);
    //void sendRAW(uint8_t *buf, uint8_t size);

private:
    void (*_TCPhandle)(shs::DTPdata &){};
    uint8_t *lens{};
    uint8_t i{};
    void *m_dtp_beg{};
};
