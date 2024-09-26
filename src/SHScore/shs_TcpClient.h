#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
*/

/*
  There is no need for this class yet.
*/

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif


#include "shs_Process.h"
#include "shs_types.h"

namespace shs
{
    class TcpClient;

};

class shs::TcpClient : public WiFiClient, public shs::Process
{
public:
    TcpClient(const uint32_t hostIP, const uint32_t port, const shs::t::shs_ID_t ID) : m_hostIP(hostIP), m_port(port) {}
    TcpClient(const char* hostIP, const uint32_t port) : TcpClient((uint32_t)IPAddress(hostIP), port) {}

    virtual ~TcpClient() = default;

    virtual void start() override { connect(m_hostIP, m_port); }

    virtual void tick() override
    {
        if (!connected())
        {
            if (connect(m_hostIP, m_port))
                write(( uint8_t* )&m_ID, sizeof(m_ID));
        }
    }

    void Process::stop() override = delete;

private:
    const uint32_t m_hostIP;
    const uint32_t m_port;
    const shs::t::shs_ID_t m_ID;
};
