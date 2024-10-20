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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace shs
{
    class TcpClient;

};

class shs::TcpClient : public WiFiClient
{
public:
    TcpClient(const uint32_t hostIP, const uint32_t port, const shs::t::shs_ID_t ID) : m_hostIP(hostIP), m_port(port) {}
    //TcpClient(const char* hostIP, const uint32_t port) : TcpClient(getIPstr(hostIP), port) {}

    virtual ~TcpClient() = default;

    void start() { connect(m_hostIP, m_port); }

    void tick()
    {
        if (!connected())
        {
            if (connect(m_hostIP, m_port))
                write(( uint8_t* )&m_ID, sizeof(m_ID));
        }
    }

private:
    const uint32_t m_hostIP;
    const uint32_t m_port;
    const shs::t::shs_ID_t m_ID;

public:    static uint32_t getIPstr(const char* IP)
    {
        uint8_t ipbytes[4] = { 0 };
        int i = 0, j = 0;
        char temp[4] = { 0 };

        for (int k = 0; k < 4; k++)
        {
            while (IP[i] != '.' && IP[i] != '\0')
            {
                if (!isdigit(IP[i]))
                {
                    return 0; // Неверный символ в IP-адресе
                }
                temp[j++] = IP[i++];
            }
            temp[j] = '\0';
            ipbytes[k] = ( uint8_t )atoi(temp);
            j = 0;
            i++;
        }

        return (ipbytes[0] << 24) | (ipbytes[1] << 16) | (ipbytes[2] << 8) | ipbytes[3];
    }
};
