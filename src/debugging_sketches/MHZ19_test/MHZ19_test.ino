#define DEBUG
#define SHS_SF_DEBUG

#include <shs_lib_MHZ19.h>
#include <shs_debug.h>

shs::MHZ19 sensor(D1, D2);

#include <MHZ19_uart.h>

MHZ19_uart mhz19;

void setup() {
  dinit();

  sensor.setup();


  // mhz19.begin(D1, D2);
  // mhz19.setAutoCalibration(false);
  // // while (mhz19.isWarming()) {
  // //   dout("MH-Z19 now warming up...  status:");
  // //   doutln(mhz19.getStatus());
  // //   delay(1000);
  // // }

  doutln("ok");
}

void loop() {
  sensor.update();
  //dout("co2: "); 
  dout(sensor.getValueF());
  dout(' ');
 // dout("temp: "); 
  doutln(sensor.getValueF(shs::MHZ19::TEMPERATURE));

  // int co2ppm = mhz19.getPPM();
  // int temp = mhz19.getTemperature();

  //  doutln(co2ppm);
  // doutln(temp);
  
  delay(5000);
}
