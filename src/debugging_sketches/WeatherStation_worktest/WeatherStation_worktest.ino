//#include <GyverBME280.h>
#include <GyverHTU21D.h>


GyverHTU21D htu;
//GyverBME280 bme;

/*
  BME280/HTU21D:
    3V3 -- VCC
    GND -- GND
    D1 (GPIO5) -- SCL
    D2 (GPIO4) -- SDA

  Photo:
    3V3 -- [PH] -- [10K] -- GND
                A0
*/
void setup() {
  Serial.begin(115200);
  Serial.println("\n");

  htu.begin() ? Serial.println("htu OK") : Serial.println("htu ERROR");
  htu.setResolution(HTU21D_RES_HIGH);

  //bme.begin(0x76) ? Serial.println("bme OK") : Serial.println("bme ERROR");

  //pinMode(A0, INPUT);
}

void loop() {
  static uint32_t tmr{};

  if (millis() - tmr >= 5000) {
    Serial.println("");
    Serial.print("htu\ntemperature:  ");
    Serial.println(htu.getTemperatureWait());
    Serial.print("humidity:     ");
    Serial.println(htu.getHumidityWait());
    Serial.println("");

    //Serial.print("bme\ntemperature:  ");
    //Serial.println(bme.readTemperature());
    //Serial.print("pressure:     ");
    //Serial.println(bme.readPressure());
    //Serial.println("");

   // Serial.print("pht\nlightness:    ");
    //Serial.println(analogRead(A0));
   // Serial.println("");
    tmr = millis();
  }
}
