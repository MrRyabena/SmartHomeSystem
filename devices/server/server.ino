#define DEBUG
#include "settings.h"
#include <SHSlibrary.h>

#include <FastBot.h>
FastBot bot(BOT_TOKEN);
FastBot abot(aBOT_TOKEN);


#include <LittleFS.h>

SHSfs shsFS(&LittleFS);

SemaphoreHandle_t wifi_mutex;
SemaphoreHandle_t sd_mutex;
SemaphoreHandle_t fs_mutex;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  connectWiFi();
  setupTCP();

  wifi_mutex = xSemaphoreCreateMutex();
  sd_mutex = xSemaphoreCreateMutex();
  fs_mutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(telegramBot, "tbot", 10000, NULL, 1, NULL, 0);
  botSetup();

}


void loop() {
  handleTCP();
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