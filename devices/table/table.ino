#include "settings.h"
#include "lighterAPI.h"
#include <SHSlibrary.h>


#include <GBUS.h>
GBUS bus(&Serial, TABLE_ID, 25);

#include <EncButton.h>
Button btn(BTNpin, INPUT, HIGH);

#include <GyverNTP.h>
GyverNTP ntp(3);

BotDebbuger bot{};


void setup() {
  Serial.begin(BUSspeed);
  connectWiFi();
  bot.send("I am started");
}

void loop() {
  //ntp.tick();
  handleBus();
  handleButton();
}
