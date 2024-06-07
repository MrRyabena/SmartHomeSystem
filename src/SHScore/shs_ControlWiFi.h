#pragma once

#include "shs_settings_private.h"
#include "shs_ID.h"

#ifdef SHS_SF_ESP8266
#include <ESP8266WiFi.h>
#elif defined(SHS_SF_ESP32)
#include <WiFi.h>
#include <esp_wifi.h>

#else
#error This file cannot be included! ESP only!

#endif

#include <shs_settings.h>

namespace shs
{
    class ControlWiFi;
};

class shs::ControlWiFi
{
public:
    bool setMac(uint8_t *mac);
    bool setMac(const shs::t::shs_ID_t id);

    bool setHostname(const char *hostname) { return WiFi.hostname(hostname); }

    void connectWiFi(const char *ssid = shs::settings::WiFi_SSID, const char *pass = shs::settings::WiFi_PASSWORD);
    bool connectWiFiWait(const size_t time = 20000, const char *ssid = shs::settings::WiFi_SSID, const char *pass = shs::settings::WiFi_PASSWORD);

    void configureWiFi(const char *ssid = shs::settings::WiFi_SSID, const char *pass = shs::settings::WiFi_PASSWORD);

    bool disableWiFi() { return WiFi.forceSleepBegin(); }
    bool enableWiFi() { return WiFi.forceSleepWake(); }

    bool WiFiConnected() { return WiFi.status() == WL_CONNECTED; }

    bool setMac(uint8_t *mac)
    {
#ifdef SHS_SF_ESP8266
        return wifi_set_macaddr(STATION_IF, mac);
#else
        return esp_wifi_set_mac(WIFI_IF_STA, mac);
#endif
    }

    bool setMac(const shs::t::shs_ID_t id)
    {
        uint8_t mac[6]{};
        for (uint8_t i = 0; i < 5; i++) mac[i] = shs::settings::MACconstant[i];
        mac[5] = id.getModuleID();

        return setMac(mac);
    }

    void connectWiFi(const char *ssid, const char *pass)
    {
        WiFi.mode(WiFi_STA);
        WiFi.begin(ssid, pass);
    }

    bool connectWiFiWait(const size_t time, const char *ssid, const char *pass)
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

    void configureWiFi(const char *ssid, const char *pass)
    {
        WiFi.mode(WiFi_STA);
        WiFi.persistent(true);
        WiFi.setAutoConnect(true);
        WiFi.setAutoReconnect(true);
        WiFi.autoConnect(ssid, pass);
    }
};
