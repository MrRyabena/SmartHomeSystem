void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D4, OUTPUT);


}

void loop() {
   static uint32_t tmr;
   static bool flag{};
   if (millis() - tmr >= 10000) {
     digitalWrite(D0, flag);
     digitalWrite(D4, !flag);
     flag = !flag;
     tmr = millis();
   }

}
