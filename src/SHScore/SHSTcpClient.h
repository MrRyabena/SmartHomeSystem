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

class shs::TcpClient : WiFiClient
{
public:
    void tick();

private:
    uint32_t _tmr = millis();
};
