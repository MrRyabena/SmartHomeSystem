#pragma once

#include "shs_settings_private.h"

#ifdef SHS_SF_ESP

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created for replace shs_connectWiFi.h.
*/

#include "shs_ID.h"
#include "shs_types.h"

#ifdef SHS_SF_ESP8266
#include <ESP8266WiFi.h>
#elif defined(SHS_SF_ESP32)
#include <WiFi.h>
#include <esp_wifi.h>

#endif

#include <shs_settings.h>

namespace shs
{
    class ControlWiFi;  // note: use [[no_unique_address]], all members are static.
};

class shs::ControlWiFi
{
public:
    static bool setHostname(const char* hostname) { return WiFi.hostname(hostname); }

    static void connectWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD)
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, pass);
    }

    static bool connectWiFiWait(const size_t time = 20000, const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD)
    {
        uint32_t tmr = millis();

        connectWiFi(ssid, pass);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            if (millis() - tmr >= time) return false;
        }
        return true;
    }

    static void configureWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD)
    {
        WiFi.mode(WIFI_STA);
        WiFi.persistent(true);
#ifndef SHS_SF_ESP32
        WiFi.setAutoConnect(true);
#endif
        WiFi.setAutoReconnect(true);
        WiFi.begin(ssid, pass);
    }

#ifndef SHS_SF_ESP32
    static bool disableWiFi() { return WiFi.forceSleepBegin(); }
    static bool enableWiFi() { return WiFi.forceSleepWake(); }
#endif

    static bool WiFiConnected() { return WiFi.status() == WL_CONNECTED; }

    static bool setMac(uint8_t* mac)
    {
    #ifdef SHS_SF_ESP8266
        return wifi_set_macaddr(STATION_IF, mac);
    #else
        return esp_wifi_set_mac(WIFI_IF_STA, mac);
    #endif
    }

    static shs::t::shs_IP_t localIP() { return WiFi.localIP(); }

    // static bool setMac(const shs::t::shs_ID_t id)
    // {
    //     uint8_t mac[6]{};
    //     for (uint8_t i = 0; i < 5; i++) mac[i] = shs::settings::MACconstant[i];
    //     mac[5] = id.getModuleID();

    //     return setMac(mac);
    // }

};

#endif  // #ifdef SHS_SF_ESP
