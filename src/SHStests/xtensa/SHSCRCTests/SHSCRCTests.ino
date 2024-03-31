#define DEBUG
#include <SHSCRCTest.h>


void setup() {
  Serial.begin(115200);
    shs::tests::CRCTest test(100000);
    test.multiplatform();
}

void loop() {}