#define DEBUG
#include "settings.h"
#include <SHSlibrary.h>
#include <esp_wifi.h>

#include <VoiceRecognitionV3.h>

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


#include <TBotCommands.h>
void TCPhandle(shs::DTPdata& stc);
const uint8_t IP[] = { 192, 168, 1, 4 };

shs::TcpServer server(IP, TCPhandle);


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
  botSetup();

  server.begin();
}

void loop() {
  xSemaphoreTake(wifi_mutex, portMAX_DELAY);
  server.tick();
  xSemaphoreGive(wifi_mutex);  
}
