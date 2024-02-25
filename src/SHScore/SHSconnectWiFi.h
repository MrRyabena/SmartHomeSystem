/*
   _____                      _     _    _                         _____           _
  / ____|                    | |   | |  | |                       / ____|         | |
 | (___  _ __ ___   __ _ _ __| |_  | |__| | ___  _ __ ___   ___  | (___  _   _ ___| |_ ___ _ __ ___
  \___ \| '_ ` _ \ / _` | '__| __| |  __  |/ _ \| '_ ` _ \ / _ \  \___ \| | | / __| __/ _ \ '_ ` _ \
  ____) | | | | | | (_| | |  | |_  | |  | | (_) | | | | | |  __/  ____) | |_| \__ \ ||  __/ | | | | |
 |_____/|_| |_| |_|\__,_|_|   \__| |_|  |_|\___/|_| |_| |_|\___| |_____/ \__, |___/\__\___|_| |_| |_|
                                                                          __/ |
                                                                         |___/
*/

/*
  Simple functions for fast wifi connection for esp8266/esp32
*/

/*

*/

#pragma once

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#include <esp_wifi.h>
#endif

#ifndef _SHS_SETTINGS_
#include <SHSsettings.h>
#endif

namespace shs
{
        void setMac(const uint8_t id);   // set mac-address SHSma + id (53:48:53:6D:61:xx xx = 0x(id))
        void setMac(const uint8_t *mac); // set mac-address

        void connectWiFi(const char *ssid, const char *pass); // wi-fi connection, called 1 time
        // String getWiFiInfo();                                 // return information
        void checkReconnection(); // call constantly, will cause a reboot if the board is disconnected from WiFi for a long time
};

void shs::connectWiFi(const char *ssid = shs::settings::WIFI_SSID, const char *pass = shs::settings::WIFI_PASSWORD)
{
        WiFi.begin(ssid, pass);
        while (WiFi.status() != WL_CONNECTED)
        {
                delay(500);
#ifdef DEBUG
                Serial.print(".");
#endif
                if (millis() > 15000)
                {
#ifndef connectWiFi_NORESTART
                        ESP.restart();
#else
                        break;
#endif
                }

#ifdef DEBUG
                Serial.println("Connected");
                Serial.print("IP: ");
                Serial.println(WiFi.localIP());
                Serial.print("Mac: ");
                Serial.println(WiFi.macAddress());
#endif
        }
}

void shs::setMac(const uint8_t id)
{
        uint8_t *mac = const_cast<uint8_t*>(shs::settings::MACconstant); // 53:48:53:6D:61:xx xx = 0x(id)
        mac[5] = id;

        WiFi.mode(WIFI_STA);
#ifdef ESP8266
        wifi_set_macaddr(STATION_IF, mac);
#else
        esp_wifi_set_mac(WIFI_IF_STA, mac);
#endif
}

void shs::setMac(const uint8_t *mac)
{
        WiFi.mode(WIFI_STA);
#ifdef ESP8266
        wifi_set_macaddr(STATION_IF, const_cast<uint8_t *>(mac));
#else
        esp_wifi_set_mac(WIFI_IF_STA, const_cast<uint8_t *>(mac));
#endif
}

// String shs::getWiFiInfo()
//  {
//          String str = "";
//          str.reserve(50);

//         str += F("IP address: ");
//         str += WiFi.localIP();
//         str += '\n';
//         str += F("ESP Mac Address: ");
//         str += (WiFi.macAddress());
//         str += '\n';
//         str += F("Subnet Mask: ");
//         str += (WiFi.subnetMask());
//         str += '\n';
//         str += F("Gateway IP: ");
//         str += (WiFi.gatewayIP());
//         str += '\n';
//         str += F("DNS: ");
//         str += (WiFi.dnsIP());

//         return str;
// }

void shs::checkReconnection()
{
        static uint32_t tmr{};
        if (WiFi.status() == WL_CONNECTED && !tmr)
                return;
        if (WiFi.status() == WL_CONNECTED)
        {
                tmr = 0;
                return;
        }
        if (WiFi.status() != WL_CONNECTED && !tmr)
                tmr = millis();
        if (tmr && millis() - tmr >= 30000)
                ESP.restart();
}
