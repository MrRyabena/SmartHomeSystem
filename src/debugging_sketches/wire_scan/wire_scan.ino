#include <Wire.h>
void setup() {
  Serial.begin(115200);
  Serial.println("Start scan");

  Wire.begin(2, 0);
}

void loop() {
  for (uint8_t i = 0; i < 255; i++) {
    Wire.beginTransmission(i);
    if (!Wire.endTransmission()) Serial.println(i, HEX);
  }
  Serial.println("...");
  delay(5000);
}
