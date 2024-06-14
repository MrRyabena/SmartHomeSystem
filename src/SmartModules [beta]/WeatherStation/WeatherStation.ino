#include <shs_ControlWiFi.h>
#include "presets.h"
#include <LittleFS.h>

#include <GyverNTP.h>

#include <GyverBME280.h>
#include <DHT.h>
#include <shs_WeatherStationData.h>

#include <shs_CRC.h>


GyverNTP ntp(3);

GyverBME280 bme;
DHT dht(DHTpin, DHT22);


void WSupdate(shs::WeatherStationData &wsd);
void WSsave(shs::WeatherStationData &wsd);

void WSbegin();
void WStick();

uint32_t WS_T = 600'000;

void setup()
{
    shs::ControlWiFi::configureWiFi();
    shs::ControlWiFi::connectWiFi();
    delay(5000);
    WSbegin();
}

void loop()
{
    ntp.tick();
    telegramBot();
    WStick();
}
