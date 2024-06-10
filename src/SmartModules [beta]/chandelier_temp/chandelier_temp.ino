#include <GyverNTC.h>
#include <SHSsettings.h>
#include <shs_ControlWiFi.h>

#define PART1_pin 13
#define PART2_pin 14
#define AC_DATA_pin 12

GyverNTC therm(A0, 10000, 3435);

bool signal_on();

void setup() {
  delay(200);
  pinMode(A0, INPUT);

  pinMode(AC_DATA_pin, INPUT);
  pinMode(PART1_pin, OUTPUT);
  pinMode(PART2_pin, OUTPUT);

  digitalWrite(PART1_pin, 0);
  digitalWrite(PART2_pin, 0);

  attachInterrupt(AC_DATA_pin, isr, RISING);

  shs::ControlWiFi::connectWiFi();


}

void loop() {
  if (shs::ControlWiFi::WiFiConnected()) {
    telegramBot();
  }

  static bool state{};
  if (signal_on() != state) {
    state = !state;
    digitalWrite(PART1_pin, state);
    digitalWrite(PART2_pin, state);
  }
}

uint64_t signal_tmr{};
IRAM_ATTR void isr() {
  signal_tmr = millis();
}


bool signal_on() {
  return !(millis() - signal_tmr >= 200);
}