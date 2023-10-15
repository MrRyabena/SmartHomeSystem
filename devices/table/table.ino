#include "settings.h"
#include "lighterAPI.h"
#include <SHSlibrary.h>


#include <GBUS.h>
GBUS bus(&Serial, TABLE_ID, 25);
DTP dtp(&bus, TABLE_ID, BUSbufsize);

#include <EncButton.h>
Button btn(BTNpin, INPUT, HIGH);

#include <GyverNTP.h>
GyverNTP ntp(3);

#include <FastBot.h>
FastBot bot(BOT_TOKEN);


void setup() {
  Serial.begin(BUSspeed);
  connectWiFi();
  botSetup();

  bot.sendMessage("I am started", CHAT_ID);
}

void loop() {
  //ntp.tick();
  bot.tick();

  handleBus();
}
