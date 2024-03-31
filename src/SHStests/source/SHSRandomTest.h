#pragma once

/*
  Testing shs::Random.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#ifdef ARDUINO
#include <SHSdebug.h>
#include <SHSRandom.h>
#else
#include "../../SHScore/SHSdebug.h"
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

  RandomTest(size_t setQuantity) : quantity(setQuantity) {}

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
  doutln("");
  doutln("Starting the test \"RandomTest::printRandomSequence\".");

  shs::Random<T> rnd(min, max);
  rnd.autoSeed();

  dout("seed: ");
  doutln(rnd.seed);
  doutln("");

  for (size_t i = 0; i < quantity; i++)
  {
    dout(rnd.get());
    dout(' ');
  }

  doutln('\n');
  doutln("Test RandomTest::printRandomSequence has completed.");
  return 0;
}

template <typename T>
[[nodiscard]] unsigned int shs::tests::RandomTest::correctRange(const T min, const T max)
{
  doutln("");
  doutln("Starting the test \"RandomTest::correctRange\".\n");
  doutln("Starting path 1.");
  shs::Random<T> rnd1(min, max);
  rnd1.autoSeed();
  dout("seed: ");
  doutln(rnd1.seed);
  for (size_t i = 0; i < quantity; i++)
    m_checkRange(rnd1.get(), min, max);

  doutln("Path 1 has completed.\nStarting path 2.");

  shs::Random<T> rnd2;
  dout("seed: ");
  doutln(rnd2.seed);
  rnd2.setRange(min, max);
  for (size_t i = 0; i < quantity; i++)
    m_checkRange(rnd2.get(), min, max);

  doutln("Path 2 has completed.\nStarting path 3.");

  shs::Random<T> rnd3;
  rnd3.setRange(min, max);
  rnd3.setSeed(42);
  dout("seed: ");
  doutln(rnd3.seed);
  for (size_t i = 0; i < quantity; i++)
    m_checkRange(rnd3.get(), min, max);

  doutln("Path 3 has completed.\n");
  doutln("Test RandomTest::correctRange has completed.");

  return 0;
}

template <typename T>
inline void shs::tests::RandomTest::m_checkRange(const T value, const T min, const T max)
{
  if (value < min)
  {
    dout("value: ");
    doutln(value);
  }
  if (value > max)
  {
    dout("value: ");
    doutln(value);
  }
}

int shs::tests::RandomTest_f(const size_t setQuantity)
{
  dout("quantity: ");
  doutln(setQuantity);
  shs::tests::RandomTest rndTest(setQuantity);
  rndTest.quantity = 100;
  int status{};
  status = rndTest.printRandomSequence<int>(-1000, 1000);
  status |= rndTest.printRandomSequence<double>(-1.005, 1.0);
  rndTest.quantity = setQuantity;
  status |= rndTest.correctRange<int>(-1000, 1000);
  status |= rndTest.correctRange<double>(-1.005, 0.948);

  return status;
}
