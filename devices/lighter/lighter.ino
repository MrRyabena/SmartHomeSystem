#include "settings.h"
#include "lighterAPI.h"
#include <SHSlibrary.h>
#include <GyverPWM.h>
#include <GBUS.h>
GBUS bus(&Serial, LIGHTER_ID, BUSbufsize);


enum Mode : uint8_t {
  off,
  on,
  
};

struct Settings {

  Mode mode = off;
  uint8_t braRval{};
  uint8_t braLval{};
  uint8_t bulbval{};
  bool flag{};

} settings;




void setup() {
  Serial.begin(BUSspeed);

  PWM_prescaler(3, 1);
  PWM_prescaler(9, 1);
  PWM_TMR1_8BIT();

  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop() {
  handleBus();
  
  fancontrol();
}