#pragma once

/*
  This is class for testing shs::ByteCollector.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include "SHSprinter.h"

#ifdef ARDUINO
#include <SHSByteCollector.h>
#include <SHSRandom.h>
#include <SHSMultiData.h>
#include <SHSMultiDataTools.h>
#else
#include "../../SHScore/SHSByteCollector.h"
#include "../../SHScore/SHSRandom.h"
#include "../utils/SHSMultiData.h"
#include "../utils/SHSMultiDataTools.h"
#endif

namespace shs
{
    namespace tests
    {
        class ByteCollectorTest;
    }
}

class shs::tests::ByteCollectorTest
{
public:
    size_t quantity;
    shs::tests::Printer out;

    ByteCollectorTest(size_t setQuantity = 10000) : quantity(setQuantity), out() {}
    
    int multiplatform();
    int sequence();
};
