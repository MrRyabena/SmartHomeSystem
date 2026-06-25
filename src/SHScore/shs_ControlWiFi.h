#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created for replace shs_connectWiFi.h.
    v2.2.0 — updated, functionality expanded:
        - The definition of functions is moved to the implementation file.
*/

#include "shs_settings_private.h"

#ifdef SHS_SF_ESP

#ifdef SHS_SF_ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#elif defined(SHS_SF_ESP32)
#include <WiFi.h>
#include <WiFiMulti.h>
#include <esp_wifi.h>
#endif

#include "shs_ID.h"
#include "shs_types.h"
#include "shs_WiFiConfig.h"


namespace shs
{
    class ControlWiFi;  // note: use [[no_unique_address]], all members are static.
};


/**
 * @brief Static helpers for configuring and connecting Wi-Fi on supported ESP targets.
 */
class shs::ControlWiFi
{
public:

#ifdef SHS_SF_ESP8266
    static bool disableWiFi();
    static bool enableWiFi();
#endif

    static bool setHostname(const char* hostname);
    static bool setMac(uint8_t* mac);

    static void connectWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD);
    static bool connectWiFiWait(const size_t time = 20000, const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD);

    #ifdef SHS_SF_WIFI_CONFIGS
    static void connectWiFiMulti(const shs::WiFiConfig* configs = shs::settings::WiFiConfigs, const uint8_t size = shs::settings::WiFiConfigs_size);
    #else 
    static void connectWiFiMulti(const shs::WiFiConfig* configs, const uint8_t size);
    #endif


    static bool WiFiConnected();
    [[nodiscard]] static shs::t::shs_IP_t getLocalIP();
    [[deprecated]] static auto localIP() { return getLocalIP(); }             // For compatibility with kernel versions below v2.2.0

    static void configureWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD);
};


#endif  // #ifdef SHS_SF_ESP
