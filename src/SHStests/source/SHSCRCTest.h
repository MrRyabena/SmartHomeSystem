#pragma once

/*
  Testing shs::CRC8, shs::CRC16, shs::CRC32.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>
#include "data.h"
#include "SHSprinter.h"

#ifdef ARDUINO
#include <SHSCRC.h>
#include <SHSRandom.h>

#else
#include "../../SHScore/SHSCRC.h"
#include "../../SHScore/SHSRandom.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#endif

namespace shs {
    namespace tests
    {
        class CRCTest;
    }
}

class shs::tests::CRCTest {
    public:
    size_t quantity;
    shs::tests::Printer out;

    CRCTest(size_t setQuantity = 10000) : quantity(setQuantity) {}
    
    int calculateCollisions();
    int multiplatform();

private:
#ifndef ARDUINO
    template <typename T>
    void printMMA(std::vector<T> v);

#endif
  
};

#ifndef ARDUINO
template <typename T>
void shs::tests::CRCTest::printMMA(std::vector<T> v)
{
    std::vector<size_t> cnts;
    std::vector<size_t> values;
    size_t sum{};
    size_t sumNulls{};

    size_t value{};
    for (auto x : v)
    {
        if (std::find(values.begin(), values.end(), x) != values.end()) continue;
        values.push_back(x);
        value = std::count(v.begin(), v.end(), x);
        if (value == 1) { sumNulls++; continue; }
        cnts.push_back(value);
        sum += value;
    }

    out.pv("min: ");
    out.pvln(static_cast<size_t>(*std::min_element(cnts.begin(), cnts.end())));
    out.pv("max: ");
    out.pvln(static_cast<size_t>(*std::max_element(cnts.begin(), cnts.end())));
    out.pv("avr: ");
    out.pvln(static_cast<double>((double)sum / v.size()));
    out.pv("     ");
    out.pvln(static_cast<double>((double)sum / std::numeric_limits<T>::max()));
    out.pv("sum: ");
    out.pvln(sum);
    out.pv("sm1: ");
    out.pvln(sumNulls);

}

#endif
