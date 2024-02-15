#include "settings.h"
#include <SHSlibrary.h>
#define K 10
BotDebbuger bot{};


void setup() {
  connectWiFi();
  Serial.begin(SPEED);
  bot.send("I have started");
}


void loop() {
 String str;
 str.reserve(20);
  if (Serial.available()) {
    str = Serial.readStringUntil('\n');
    bot.send(str);
  }

  static uint32_t tmr{};
  if (millis() - tmr >= 5000) {
    Serial.println("Hello");
    tmr = millis();
  }
}
