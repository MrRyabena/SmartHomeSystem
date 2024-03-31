#define DEBUG
#include "SHSRandomTest.h"


#include <SHSdebug.h>

void setup() {
  Serial.begin(115200);
  doutln("starting!");
  shs::tests::RandomTest_f();
  doutln("end!");
}

void loop() {}