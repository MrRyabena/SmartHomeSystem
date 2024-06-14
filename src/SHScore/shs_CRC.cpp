#include "shs_CRC.h"

/*
  ----------------------------------------
  CRC 8
  ----------------------------------------
*/

void shs::CRC8::update(uint8_t &crc, uint8_t data)
{
    // this is algorithm from Alex Gyver: https://github.com/GyverLibs/GyverBus/blob/46fa3fc0510673a4e48e12e71030a81cde14ac24/src/GyverBus.cpp#L22
#if defined(__AVR__)
    // fast algorithm for AVR
    uint8_t counter;
    uint8_t buffer;
    asm volatile(
        "EOR %[crc_out], %[data_in] \n\t"
        "LDI %[counter], 8          \n\t"
        "LDI %[buffer], 0x8C        \n\t"
        "_loop_start_%=:            \n\t"
        "LSR %[crc_out]             \n\t"
        "BRCC _loop_end_%=          \n\t"
        "EOR %[crc_out], %[buffer]  \n\t"
        "_loop_end_%=:              \n\t"
        "DEC %[counter]             \n\t"
        "BRNE _loop_start_%="
        : [crc_out] "=r"(crc), [counter] "=d"(counter), [buffer] "=d"(buffer)
        : [crc_in] "0"(crc), [data_in] "r"(data));
#else
    // for the rest
    uint8_t i = 8;
    while (i--)
    {
        crc = ((crc ^ data) & 1) ? (crc >> 1) ^ 0x8C : (crc >> 1);
        data >>= 1;
    }
#endif
}

uint8_t shs::CRC8::crcBuf(const uint8_t *ptr, uint16_t size)
{
    //uint8_t crc = 0;
    for (uint16_t i = 0; i < size; i++)
        update(crc, *ptr);
    return crc;
}

/*
  ----------------------------------------
  CRC 16
  ----------------------------------------
*/

void shs::CRC16::update(uint16_t &crc, uint8_t data)
{
    uint16_t x{};
    x = crc >> 8 ^ data++;
    x ^= x >> 4;
    crc = (crc << 8) ^ ((uint16_t)(x << 12) ^ ((uint16_t)(x << 5)) ^ x);
}

uint16_t shs::CRC16::crcBuf(const uint8_t *ptr, uint16_t size)
{

    //uint16_t crc = 0xFFFF;

    while (size--)
    {
        update(crc, *ptr++);
    }
    return crc;
}

/*
  ----------------------------------------
  CRC 32
  ----------------------------------------
*/

void shs::CRC32::update(uint32_t &crc, uint8_t data)
{
    crc ^= 0xFFFFFFFF;
    crc ^= data;
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xEDB88320;
        else
            crc = (crc >> 1);
    }
    crc ^= 0xFFFFFFFF;
}

uint32_t shs::CRC32::crcBuf(const uint8_t *ptr, uint16_t size)
{
    //uint32_t crc = 0; // 0xFFFFFFFF;
    while (size--)
    {
        update(crc, *ptr++);
    }
    return crc; // ^ 0xFFFFFFFF;
}
