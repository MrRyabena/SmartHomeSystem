#include <GyverBME280.h>
#include <DHT.h>

#define DHTpin D6
#define RAINSENSORpin D7

GyverBME280 bme;
DHT dht(DHTpin, DHT22);

/*
  BME280/HTU21D:
    3V3 --------- VCC
    GND --------- GND
    D1 (GPIO5) -- SCL
    D2 (GPIO4) -- SDA

  DHT22:
    3V3 ----- VCC
    GND ----- GND
    DHTpin -- DATA

  RainSensor:
    3V3 ------------ VCC
    GND ------------ GND
    RAINSENSORpin -- DO

  Photo:
    3V3 -- [PH] -- [10K] -- GND
                A0
*/
void setup() {
  Serial.begin(115200);
  Serial.println("\n");

  bme.begin(0x76) ? Serial.println("bme OK") : Serial.println("bme ERROR");
  dht.begin();
  pinMode(RAINSENSORpin, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  static uint32_t tmr{};

  if (millis() - tmr >= 5000) {

    Serial.println("\n----------------------------------------");

    Serial.print("bme\ntemperature:   ");
    Serial.println(bme.readTemperature());
    Serial.print("pressure:      ");
    Serial.println(bme.readPressure());

    Serial.println("");

    Serial.print("dht\ntemperature:   ");
    Serial.println(dht.readTemperature());
    Serial.print("humidity:      ");
    Serial.println(dht.readHumidity());

    Serial.println("");

    Serial.print("rain_sensor\nrain_now:      ");
    Serial.println(!digitalRead(RAINSENSORpin));

    Serial.println("");

    Serial.print("pht\nillumination:  ");
    Serial.println(analogRead(A0));
    
    Serial.println("----------------------------------------\ n");
    
    
    tmr = millis();
  }
}
