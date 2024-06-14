#include <Wire.h>
void setup() {
  Serial.begin(115200);
  Serial.println("Start scan");

  Wire.begin();
}

void loop() {
  for (uint8_t i = 1; i < 128; i++) {
    Wire.beginTransmission(i);
    if (!Wire.endTransmission()) Serial.println(i, HEX);
  }
  Serial.println("...");
  delay(5000);
}
