#include "settings.h"

#include <GyverNTC.h>
GyverNTC therm(A0, 10000, 3435);


void setup() {
  Serial.begin(SPEED);
  pinMode(A0, INPUT);
}


void loop() {
  String str{};
  if (Serial.available()) {
    str = Serial.readStringUntil('\n');
    Serial.println(str);
  }

  static uint32_t tmr{};
  if (millis() - tmr >= 5000) {
    Serial.print("T ");
    Serial.println(therm.getTempAverage());
    tmr = millis();
  }
}
