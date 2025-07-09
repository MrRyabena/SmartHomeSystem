#include "shs_ControlWiFi.h"


bool shs::ControlWiFi::setHostname(const char* hostname)
{
    return WiFi.hostname(hostname);
}


void shs::ControlWiFi::connectWiFi(const char* ssid, const char* pass)
{
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
}


bool shs::ControlWiFi::connectWiFiWait(const size_t time, const char* ssid, const char* pass)
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


void shs::ControlWiFi::configureWiFi(const char* ssid, const char* pass)
{
    WiFi.mode(WIFI_STA);
    WiFi.persistent(true);
#ifdef SHS_SF_ESP8266
    WiFi.setAutoConnect(true);
#endif
    WiFi.setAutoReconnect(true);
    WiFi.begin(ssid, pass);
}


#ifndef SHS_SF_ESP32
bool shs::ControlWiFi::disableWiFi() { return WiFi.forceSleepBegin(); }
bool shs::ControlWiFi::enableWiFi() { return WiFi.forceSleepWake(); }
#endif


bool shs::ControlWiFi::WiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}


shs::t::shs_IP_t shs::ControlWiFi::getLocalIP()
{
    return WiFi.localIP();
}


bool shs::ControlWiFi::setMac(uint8_t* mac)
{
#ifdef SHS_SF_ESP8266
    return wifi_set_macaddr(STATION_IF, mac);
#else
    return esp_wifi_set_mac(WIFI_IF_STA, mac);
#endif
}
