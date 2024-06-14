#include <shs_ControlWiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nstarted");

  shs::ControlWiFi cwf;
  
  cwf.connectWiFiWait() ? Serial.println("Connected!") : Serial.println("Error!");

  cwf.setHostname("PScontroller");
  Serial.println("end.");
}

void loop() {
  // put your main code here, to run repeatedly:
}
