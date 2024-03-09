uint8_t RGBmode{};

void RGB() {
  switch (RGBmode) {
    case 0:
      strip.setRGB(0, 0, 0);
      break;
    case 1:
      fireTick();
      break;

    case 2:
      task_3();
      break;
  }
}

/*
   Белый (RGB) свет с настройкой яркости.
*/
/*
void task_0() {
  int val;

//   if (s == 2) {
//     val = map(analogRead(0), 0, 1023, 0, 255);
//   }
  //else val = Pbright;
  val = 255;

  analogWrite(R_p, val);
  analogWrite(G_p, val);
  analogWrite(B_p, val);
}
*/

/*
  Белый свет с регулировкой температуры (1000—32000 °K)
*/
/*
void task_1() {

  //GRGB strip(R_p, G_p, B_p);  // куда подключены цвета (R, G, B)
  int kelvin;

  if (s == 2) kelvin = map(analogRead(0), 0, 255, 1000, 32000);
  else kelvin = Pkelvin;
  strip.setKelvin(kelvin);
//  if (kelvin_s != kelvin) {
//    //Serial.print("kelvin = ");
//    //Serial.println(kelvin);
//    kelvin_s = kelvin;
//  }

}
*/

/*
   Динамическая смена цвета по колесу (1530 значений, настраиваемая скорость)
*/
void task_3() {

  int tm = 40;
  // tm = 20;
  //   if (s == 1) {
  //     tm = map(analogRead(0), 0, 1023, 0, 50);
  //   }
  static uint32_t tmr{};
  static int VAL{};

  if (millis() - tmr >= tm) {
    // Serial.println(tm);
    tmr = millis();
    VAL++;
  }
  if (VAL >= 1530) {
    VAL = 0;
  }
  strip.setWheel(VAL);
}

/*
   Унстановить цвет по значению колеса (1530 оттенков)
*/
void task_4() {

  // if (String(buff)[1] == 0){
  // GRGB strip(R_p, G_p, B_p);  // куда подключены цвета (R, G, B)

  // strip.colorWheel(map(analogRead(0), 0, 1023, 0, 1530));

  //   }
  //   else {

  //   }

  //  analogWrite(R_p, strip.showR);
  //  analogWrite(G_p, strip.showG);
  //  analogWrite(B_p, strip.showB);
}

/*
   Установить цвет, вручную смешивая RGB потенциометром
*/
void task_5() {
  /*
      //  int r, g, b;
      //
      //  if (s == 1) {
      //    r = map(analogRead(0), 0, 1023, 0, 255);
      //  }
      //
      //  else if (s == 2) {
      //    g = map(analogRead(0), 0, 1023, 0, 255);
      //  }
      //
      //  else if (s == 3) {
      //    b = map(analogRead(0), 0, 1023, 0, 255);
      //  }
      //
      //
      analogWrite(R_p, Pred);
      analogWrite(G_p, Pgreen);
      analogWrite(B_p, Pblue);

    */
}

void fireTick() {

  static uint32_t prevTime, prevTime2;
  static byte fireRnd = 0;
  static float fireValue = 0;

  // задаём направление движения огня
  if (millis() - prevTime > 100) {
    prevTime = millis();
    fireRnd = random(0, 10);
  }
  // двигаем пламя
  if (millis() - prevTime2 > 20) {
    prevTime2 = millis();
    fireValue = (float)fireValue * (1 - SMOOTH_K) + (float)fireRnd * 10 * SMOOTH_K;
    strip.setHSV(
      constrain(map(fireValue, 20, 60, HUE_START, HUE_START + HUE_GAP), 0, 255),  // H
      constrain(map(fireValue, 20, 60, MAX_SAT, MIN_SAT), 0, 255),                // S
      constrain(map(fireValue, 20, 60, MIN_BRIGHT, MAX_BRIGHT), 0, 255)           // V
    );
  }
}
