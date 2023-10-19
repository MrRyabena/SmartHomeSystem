void fancontrol() {
  static uint32_t tmr = millis();

  if (millis() - tmr >= 5000) {
    // if (settings.mode) analogWrite(FANpin, 0);
    //else {
      // float temp = getThermTemp(getAnalogAverage(FANth));
      // // 𝑦=(7𝑡+1,4𝑎)  t [0;30] a[0;100]
      uint16_t pwm{}; //= static_cast<uint16_t>(temp);
      // pwm = map(pwm, 30, 50, 0, 30);
      // pwm *= 7;
      pwm =settings.braRval + settings.braLval;
      pwm >> 1;

      settings.pwm = (uint8_t)pwm; //map(pwm, 0, 255, 0, 255);
      analogWrite(FANpin, settings.pwm);

    //}
    tmr = millis();
  }
}


void isr() {
  tach.tick();
}
#define RESIST_BASE 10000   // сопротивление при TEMP_BASE градусах по Цельсию (Ом)
#define TEMP_BASE 25        // температура, при которой измерено RESIST_BASE (градусов Цельсия)
#define B_COEF 3435  
#define RESIST_10K 9700    // точное сопротивление 10к резистора (Ом)

float getThermTemp(int resistance) {
  float thermistor{};
  thermistor = RESIST_10K / ((float)1023 / resistance - 1);
  thermistor /= RESIST_BASE;                        // (R/Ro)
  thermistor = log(thermistor) / B_COEF;            // 1/B * ln(R/Ro)
  thermistor += (float)1.0 / (TEMP_BASE + 273.15);  // + (1/To)
  thermistor = (float)1.0 / thermistor - 273.15;    // инвертируем и конвертируем в градусы по Цельсию
  return thermistor;
}

