void fancontrol() {
  static uint32_t tmr = millis();

  if (millis() - tmr >= 5000) {
    if (settinngs.mode) analogWrite(FANpin, 0);
    else {
      float temp = getAnalogAverage(FANth);
      // 𝑦=(7𝑡+1,4𝑎)  t [0;30] a[0;100]
      uint16_t pwm = static_cast<uint16_t>(temp);
      pwm = map(pwm, 30, 50, 0, 30);
      pwm *= 7;
      pwm += (settings.braRval + settings.braLval) * 0.2;

      analogWrite(FANpin, map(pwm, 0, 350, 0, 255);
    }
    tmr = millis();
  }
}