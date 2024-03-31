#pragma once

/*
  Simple class for setting output data.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>

#define DEBUG

#ifdef ARDUINO
#include <SHSdebug.h>
#else
#include "../../SHScore/SHSdebug.h"
#endif

namespace shs
{
    namespace tests
    {
      class Printer;
    }
}

class shs::tests::Printer {
public:
    uint8_t flags;
    
    Printer() : flags(0xff) {}

    constexpr void print_main_information(const bool flag) { flag ? flags |= 1 : flags &= ~1; }
    constexpr void print_secondary_information(const bool flag) { flag ? flags |= (1 << 1) : flags &= ~(1 << 1); }
    constexpr void print_values(const bool flag) { flag ? flags |= (1 << 2) : flags &= ~(1 << 2); }
    constexpr void print_notes(const bool flag) { flag ? flags |= (1 << 3) : flags &= ~(1 << 3); }
    constexpr void print_separator(const bool flag) { flag ? flags |= (1 << 4) : flags &= ~(1 << 4); }

    template <typename T>
    void pm(const T &value) { if (flags & 1) dout(value); }
    template <typename T>
    void pmln(const T& value) { if (flags & 1) doutln(value); }

    template <typename T>
    void ps(const T& value) { if (flags & (1 << 1)) dout(value); }
    template <typename T>
    void psln(const T &value) { if (flags & (1 << 1)) doutln(value); }

    template <typename T>
    void pv(const T &value) { if (flags & (1 << 2)) dout(value); }
    template <typename T>
    void pvln(const T &value) { if (flags & (1 << 2)) doutln(value); }
    
    template <typename T>
    void pn(const T &value) { if (flags & (1 << 3)) dout(value); }
    template <typename T>
    void pnln(const T &value) { if (flags & (1 << 3)) doutln(value); }

    void sep() const { if (flags & (1 << 4)) dsep(); }

};
