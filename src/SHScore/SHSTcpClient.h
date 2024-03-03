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

#include "SHSByteCollector.h"
#include "SHSdtp.h"

namespace shs
{
    class TcpClient;

};

class shs::TcpClient : public WiFiClient
{
public:
    void tick();

protected:
    uint32_t _tmr = millis();
};
