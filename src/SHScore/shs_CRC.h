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
    static constexpr uint8_t CRC8_beg = 0x00;
    uint8_t crc{};
    explicit CRC8() : crc(CRC8_beg) {}

    void add(const uint8_t value) { update(crc, value); }
    void clear() { crc = CRC8_beg; }

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
    static constexpr uint16_t CRC16_beg = 0xFFFF;
    uint16_t crc{};
    CRC16() : crc(CRC16_beg) {}

    void add(const uint8_t value) { update(crc, value); }
    void clear() { crc = CRC16_beg; }

    void update(uint16_t& crc, const uint8_t data);
    uint16_t crcBuf(const uint8_t* ptr, uint16_t size);
};

/*
  CRC 32
*/

class shs::CRC32
{
public:
    static constexpr uint32_t CRC32_beg = 0x00000000;
    uint32_t crc{};
    explicit CRC32() : crc(CRC32_beg) {}

    void add(const uint8_t value) { update(crc, value); }
    void clear() { crc = CRC32_beg; }

    void update(uint32_t& crc, uint8_t data);
    uint32_t crcBuf(const uint8_t* ptr, uint16_t size);
};
