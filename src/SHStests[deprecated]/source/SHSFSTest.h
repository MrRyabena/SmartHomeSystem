#pragma once

/*
  Testing shs::File
*/

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
*/

#include <stdint.h>
#include "SHSprinter.h"

#ifdef ARDUINO
#include <SHSFile.h>
#include <SHSRandom.h>

#else
#include "../../SHScore/SHSFile.h"
#include "../../SHScore/SHSFS.h"
#include "../../SHScore/SHSshsf.h"
#include "../../SHScore/SHSRandom.h"
#include <fstream>
#endif

namespace shs
{
  namespace tests
  {
    class FSTest;
  }
}

class shs::tests::FSTest
{
public:
  size_t quantity;
  shs::tests::Printer out;
  FSTest(size_t setQuantity = 10000) : quantity(setQuantity) {}

  int simpleFile();
  int simpleSHSF();

  int shsfFull();

  // utils
  void logFile(shs::File& file);
};
