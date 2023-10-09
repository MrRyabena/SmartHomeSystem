#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include "settings.h"




void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
#ifdef DEBUG
        Serial.print(".");
#endif
        if (millis() > 15000) {
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