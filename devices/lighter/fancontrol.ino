
GyverNTC th0(A0, 10000, 3450, 25, 22000);
GyverNTC th1(A1, 10000, 3950, 25, 20000);

void fancontrol() {
  static uint32_t tmr = millis();

  if (millis() - tmr >= 5000) {
    // if (settings.mode) analogWrite(FANpin, 0);
    //else {
    // float temp = getThermTemp(getAnalogAverage(FANth));
    // Serial.println(th0.getTempAverage(A0));
    // Serial.println(th1.getTempAverage(A1));

    // Serial.println(analogRead(FANth));
    // Serial.println(analogRead(A1));
    // Serial.println();
    // // 𝑦=(7𝑡+1,4𝑎)  t [0;30] a[0;100]
    uint16_t pwm{};  //= static_cast<uint16_t>(temp);
    // pwm = map(pwm, 30, 50, 0, 30);
    // pwm *= 7;
    // pwm =settings.braRval + settings.braLval;
    // pwm >> 1;
    pwm = settings.braRval || settings.braLval;
    settings.pwm = (uint8_t)pwm;  //map(pwm, 0, 255, 0, 255);
    digitalWrite(FANpin, settings.pwm);

    //}
    tmr = millis();
  }
}


// ISR(PCINT0_vect) {  // пины 8-13
//   tach.tick();
// }


void isr() {
  tach.tick();
}



// // функция для настройки PCINT
// uint8_t attachPCINT(uint8_t pin) {
//   if (pin < 8) {  // D0-D7 (PCINT2)
//     PCICR |= (1 << PCIE2);
//     PCMSK2 |= (1 << pin);
//     return 2;
//   } else if (pin > 13) {  //A0-A5 (PCINT1)
//     PCICR |= (1 << PCIE1);
//     PCMSK1 |= (1 << pin - 14);
//     return 1;
//   } else {  // D8-D13 (PCINT0)
//     PCICR |= (1 << PCIE0);
//     PCMSK0 |= (1 << pin - 8);
//     return 0;
//   }
// }