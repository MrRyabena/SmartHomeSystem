#pragma once

/*
  Testing shs::Random.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include "SHSprinter.h"

#ifdef ARDUINO
#include <SHSRandom.h>
#else
#include "../../SHScore/SHSRandom.h"
#endif

namespace shs
{
    namespace tests
    {
      class RandomTest;
      int RandomTest_f(const size_t setQuantity = 10000000);
    }
}

class shs::tests::RandomTest
{
public:
  size_t quantity;
  shs::tests::Printer out;

  RandomTest(size_t setQuantity = 100000) : quantity(setQuantity) {}

  template <typename T>
  unsigned int printRandomSequence(const T min, const T max);

  template <typename T>
  unsigned int correctRange(const T min, const T max);

protected:
  template <typename T>
  void m_checkRange(const T value, const T min, const T max);
};

template <typename T>
[[nodiscard]] unsigned int shs::tests::RandomTest::printRandomSequence(const T min, const T max)
{
  out.sep();
  out.pmln("Starting the test \"RandomTest::printRandomSequence\".");

  shs::Random<T> rnd(min, max);
  rnd.autoSeed();

  out.pn("seed: ");
  out.pnln(rnd.seed);
  out.pvln("");

  for (size_t i = 0; i < quantity; i++)
  {
    out.pv(rnd.get());
    out.pv(' ');
  }

  out.pvln('\n');
  out.pmln("Test RandomTest::printRandomSequence has completed.");
  return 0;
}

template <typename T>
[[nodiscard]] unsigned int shs::tests::RandomTest::correctRange(const T min, const T max)
{
  out.sep();
  out.pmln("Starting the test \"RandomTest::correctRange\".");
  out.psln("Starting path 1.");
  shs::Random<T> rnd1(min, max);
  rnd1.autoSeed();
  out.pn("seed: ");
  out.pnln(rnd1.seed);
  for (size_t i = 0; i < quantity; i++)
    m_checkRange(rnd1.get(), min, max);

  out.psln("Path 1 has completed.\nStarting path 2.");

  shs::Random<T> rnd2;
  out.pn("seed: ");
  out.pnln(rnd2.seed);
  rnd2.setRange(min, max);
  for (size_t i = 0; i < quantity; i++)
    m_checkRange(rnd2.get(), min, max);

  out.psln("Path 2 has completed.\nStarting path 3.");

  shs::Random<T> rnd3;
  rnd3.setRange(min, max);
  rnd3.setSeed(42);
  out.pn("seed: ");
  out.pnln(rnd3.seed);
  for (size_t i = 0; i < quantity; i++)
    m_checkRange(rnd3.get(), min, max);

  out.psln("Path 3 has completed.\n");
  out.pmln("Test RandomTest::correctRange has completed.");
  out.sep();
  return 0;
}

template <typename T>
inline void shs::tests::RandomTest::m_checkRange(const T value, const T min, const T max)
{
  if (value < min)
  {
    out.pv("value: ");
    out.pvln(value);
  }
  if (value > max)
  {
    out.pv("value: ");
    out.pvln(value);
  }
}

int shs::tests::RandomTest_f(const size_t setQuantity)
{
  shs::tests::RandomTest rndTest(setQuantity);
  rndTest.out.pn("quantity: ");
  rndTest.out.pnln(setQuantity);
  rndTest.quantity = 100;
  int status{};
  status = rndTest.printRandomSequence<int>(-1000, 1000);
  status |= rndTest.printRandomSequence<double>(-1.005, 1.0);
  rndTest.quantity = setQuantity;
  status |= rndTest.correctRange<int>(-1000, 1000);
  status |= rndTest.correctRange<double>(-1.005, 0.948);

  return status;
}
