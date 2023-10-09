#include "settings.h"
#include <SHSlibrary>


#include <GBUS.h>
GBUS bus(&Serial, TABLE_ID, 25);

#include <EncButton.h>
Button btn(BTNpin, INPUT, HIGH);

#include <GyverNTP.h>
GyverNTP ntp(3);


void setup() {
  Serial.begin(TABLE_BUSspeed);
  connectWiFi();
}

void loop() {
  ntp.tick();
  handleBus();
  handleButton();
}
