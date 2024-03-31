#define DEBUG
#include "SHSCRCTest.h"


void setup() {
    shs::tests::CRCTest test(100000);
    test.multiplatform();
}

void loop() {}