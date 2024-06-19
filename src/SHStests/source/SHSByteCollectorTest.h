#pragma once

/*
  This is class for testing shs::ByteCollector.
*/

/*
  Last update: v2.0.0
  Versions:
    v1.1.0 — created.
    v2.0.0
*/



#ifdef ARDUINO
#include <SHSByteCollector.h>
#include <SHSRandom.h>
#include <SHSMultiData.h>
#include <SHSMultiDataTools.h>
#else
#include "../../SHScore/shs_ByteCollector.h"
#include "../../SHScore/SHSRandom.h"
#include "../utils/SHSMultiData.h"
#include "../utils/SHSMultiDataTools.h"
#endif

#include <assert.h>

#include "SHSprinter.h"

namespace shs
{
    namespace tests
    {
        class ByteCollector_test;
    };
};

class shs::tests::ByteCollector_test
{
public:
    size_t quantity;
    shs::tests::Printer out;

    ByteCollector_test(size_t setQuantity = 10000) : quantity(setQuantity), out() {}
    
    int write_read_test();
    int add_get_test();
    int reserve_test();
    int insert_test();
    int shrink_to_fit_test();


    int multiplatform();
    int sequence();
    void myTest();
};
