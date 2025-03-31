#define DEBUG
#include "../../source/SHSCRCTest.h"


int main()
{
    shs::tests::CRCTest test(100000);
    test.calculateCollisions();
    return test.multiplatform();
}
