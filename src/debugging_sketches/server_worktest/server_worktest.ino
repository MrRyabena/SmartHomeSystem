void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);

}

void loop() {
  static uint32_t tmr{};
  static bool led{};
  if (millis() - tmr >= 1000) {
    digitalWrite(2, led);
    led = !led;
    tmr = millis();
  }

}
