#pragma once
#include <stdint.h>

/*
 __ _  __
/  |_)/
\__| \\__

*/

/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v1.1.0 — now the function crcBuf(..) writes the result to a variable crc.
    v1.2.0 — optimized.
    v2.0.0 — added static methods in shs::CRC8, fixed bugs.
*/

/*
  Note: The code needs to be refactored. Make transformations in the C++ style.
  Make the same functionality static and instance:
    instance:
      - add()
      - addBuf()
      - clear()

    static:
      - update()
      - crcBuf()
      - updateBuf()

*/

namespace shs
{
    class CRC8;
    class CRC16;
    class CRC32;
};

/*
  CRC 8
*/

class shs::CRC8
{
public:
    static constexpr uint8_t CRC8_poly = 0x00;
    uint8_t crc{};
    explicit CRC8() : crc(CRC8_poly) {}

    void add(const uint8_t value) { update(crc, value); }
    void clear() { crc = CRC8_poly; }

    static void update(uint8_t& crc, const uint8_t data);
    uint8_t addBuf(const uint8_t* ptr, uint16_t size);

    static uint8_t crcBuf(const uint8_t* ptr, uint16_t size);
};

/*
  CRC 16
*/

class shs::CRC16
{
public:
    static constexpr uint16_t CRC16_poly = 0xFFFF;
    uint16_t crc{};
    CRC16() : crc(CRC16_poly) {}

    void add(const uint8_t value) { update(crc, value); }
    void clear() { crc = CRC16_poly; }

    void update(uint16_t& crc, const uint8_t data);
    uint16_t crcBuf(const uint8_t* ptr, uint16_t size);
};

/*
  CRC 32
*/

class shs::CRC32
{
public:
    static constexpr uint32_t CRC32_poly = 0x00000000;
    uint32_t crc{};
    explicit CRC32() : crc(CRC32_poly) {}

    void add(const uint8_t value) { update(crc, value); }
    void clear() { crc = CRC32_poly; }

    void update(uint32_t& crc, uint8_t data);
    uint32_t crcBuf(const uint8_t* ptr, uint16_t size);
};
