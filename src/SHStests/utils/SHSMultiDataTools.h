#pragma once

#include "SHSMultiData.h"
#include <stdint.h>

#define DEBUG

#ifdef ARDUINO
#include <SHSRandom.h>
#include <SHSdebug.h>
#else
#include "../../SHScore/SHSRandom.h"
#include "../../SHScore/SHSdebug.h"
#endif

namespace shs
{
    namespace tests
    {
        class MultiDataTools;
    }
}

class shs::tests::MultiDataTools
{
public:
    void randomFill(shs::tests::MultiData &data);
    void print(shs::tests::MultiData &data);
    void printBytesArray(shs::tests::MultiData &data);
};
