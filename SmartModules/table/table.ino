#include "settings.h"
#include "lighterAPI.h"
#include <SHSlibrary.h>
#include <TableAPI.h>

uint8_t IP[] = { 192, 168, 1, 5 };

#include <GBUS.h>
GBUS bus(&Serial, IP[3], 25);
//DTP dtp(&bus, IP[3], BUSbufsize);

#include <EncButton.h>
Button btn(BTNpin, INPUT, HIGH);

#include <GyverNTP.h>
GyverNTP ntp(3);

#include <FastBot.h>
FastBot bot(BOT_TOKEN);

void TCPhandle(shs::DTPdata &stc);

shs::TcpClient client(IP, TCPhandle);

//#include <FastLed.h>


uint8_t dur{};

void setup() {
  Serial.begin(BUSspeed);

  WiFi.mode(WIFI_STA);
  wifi_set_macaddr(0, const_cast<uint8_t *>(MAC));

  shs::connectWiFi();
  //botSetup();
}

void loop() {
  // ntp.tick();
  //bot.tick();
  client.tick();
  //sunrise(dur);
  //handleBus();
}
