#define DEBUG
#include "settings.h"
// #include <SHSlibrary.h>
#include <esp_wifi.h>
#include <SHSsettings.h>
#include <SHSByteCollector.h>
#include <SHSconnectWiFi.h>
#include <SHSfs.h>
#include <SHSdtp.h>
#include <SHSalgoritm.h>

#include <FastBot.h>
FastBot bot(BOT_TOKEN);
FastBot abot(aBOT_TOKEN);

#include <LittleFS.h>

shs::SHSfs shsFS(&LittleFS);

SemaphoreHandle_t wifi_mutex;
SemaphoreHandle_t sd_mutex;
SemaphoreHandle_t fs_mutex;
void botSetup();
void setupTCP();
void handleTCP();

#include <WiFiServer.h>
#include <WiFiClient.h>


WiFiServer server(80);
WiFiClient clients[MAX_WIFICLIENTS];
uint8_t lens[MAX_WIFICLIENTS]{};


void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, SERVER_MAC);

  shs::connectWiFi();
  pinMode(2, OUTPUT);
  if (WiFi.status() == WL_CONNECTED) digitalWrite(2, 0);

  wifi_mutex = xSemaphoreCreateMutex();
  sd_mutex = xSemaphoreCreateMutex();
  fs_mutex = xSemaphoreCreateMutex();

  //xTaskCreatePinnedToCore(telegramBot, "tbot", 10000, NULL, 1, NULL, 0);
  //botSetup();
  setupTCP();
}

void loop() {
  handleTCP();

  static uint32_t tmr = millis();
  if (millis() - tmr >= 5000) {
    for (uint8_t i = 0; i < MAX_WIFICLIENTS; i++) {
      if (clients[i]) {
        shs::ByteCollector col(13);
        col.add("Hello, user!");
        for (uint8_t i = 0; i < col.size(); i++) Serial.println(col.buf[i]);
        Serial.println(clients[i].remoteIP());
        shs::DTP dtp(SERVER_ID);
        dtp.packDTP(&col, 127);
        
        Serial.println();
        for (uint8_t i = 0; i < col.size(); i++) Serial.println(col.buf[i]);
        Serial.println();
        Serial.println(col.buf[col.buf[0] - 1]);
        Serial.println(shs::crc_8(col.buf, col.size() - 1));
        Serial.println();
        clients[i].write(col.buf, col.size());

        //clients[i].write("Hello, user!");
      }
    }
    tmr = millis();
  }

  
}


// void handleClient() {
//   WiFiClient client = server.available();
//   if (client) {
//     while (client) {
//       while (client.available() > 0) {
//         char c = client.read();
//         Serial.print(c);
//       }
//       // delay(10);
//       // answer
//       client.println("I am glad to see you too!");
//     }
//   }
//   client.stop();
// }