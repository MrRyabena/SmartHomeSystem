
#include <GyverNTC.h>
GyverNTC therm(A0, 10000, 3435);


void setup() {
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  if (therm.getTempAverage() <= 30 && therm.getTempAverage() >= 15) digitalWrite(13, 1);
  else digitalWrite(13, 0);

  static uint32_t tmr = millis();
  static uint8_t pwm = 200;
  if (millis() - tmr >= 5000) {
    if (pwm) pwm = 0;
    else pwm = 200;
    digitalWrite(11, pwm);
    tmr = millis();
  }
}
