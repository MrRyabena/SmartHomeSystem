#pragma once

/*
  Tools for struct MultiData.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include "SHSMultiData.h"
#include <stdint.h>

#include "../source/SHSprinter.h"

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
    shs::tests::Printer out;

    void randomFill(shs::tests::MultiData &data);
    void print(shs::tests::MultiData &data);
    void printBytesArray(shs::tests::MultiData &data);
};
