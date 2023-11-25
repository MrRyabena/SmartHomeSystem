/*
   _____                      _     _    _                         _____           _
  / ____|                    | |   | |  | |                       / ____|         | |
 | (___  _ __ ___   __ _ _ __| |_  | |__| | ___  _ __ ___   ___  | (___  _   _ ___| |_ ___ _ __ ___
  \___ \| '_ ` _ \ / _` | '__| __| |  __  |/ _ \| '_ ` _ \ / _ \  \___ \| | | / __| __/ _ \ '_ ` _ \
  ____) | | | | | | (_| | |  | |_  | |  | | (_) | | | | | |  __/  ____) | |_| \__ \ ||  __/ | | | | |
 |_____/|_| |_| |_|\__,_|_|   \__| |_|  |_|\___/|_| |_| |_|\___| |_____/ \__, |___/\__\___|_| |_| |_|
                                                                          __/ |
                                                                         |___/
*/

#pragma once

// CRC
namespace shs
{
    const uint8_t CRC8_beg = 0x00;
    const uint16_t CRC16_beg = 0xFFFF;
    const uint32_t CRC32_beg = 0x00000000;

    inline uint8_t crc_8(const uint8_t *ptr, uint16_t size);
    inline void crc_8_update(uint8_t &crc, uint8_t data);

    inline uint16_t crc_16(const uint8_t *ptr, uint16_t size);
    inline void crc_16_update(uint16_t &crc, uint8_t data);

    inline uint32_t crc_32(const uint8_t *ptr, uint16_t size);
    inline void crc_32_update(uint32_t &crc, uint8_t data);

};

/*
 __ _  __
/  |_)/
\__| \\__

*/

inline void shs::crc_8_update(uint8_t &crc, uint8_t data)
{
#if defined(__AVR__)
    // резкий алгоритм для AVR
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
    // обычный для всех остальных
    uint8_t i = 8;
    while (i--)
    {
        crc = ((crc ^ data) & 1) ? (crc >> 1) ^ 0x8C : (crc >> 1);
        data >>= 1;
    }
#endif
}

inline uint8_t shs::crc_8(const uint8_t *ptr, uint16_t size)
{
    uint8_t crc = 0;
    for (uint16_t i = 0; i < size; i++)
        shs::crc_8_update(crc, *ptr);
    return crc;
}

inline void shs::crc_16_update(uint16_t &crc, uint8_t data)
{
    uint16_t x{};
    x = crc >> 8 ^ data++;
    x ^= x >> 4;
    crc = (crc << 8) ^ ((uint16_t)(x << 12) ^ ((uint16_t)(x << 5)) ^ x);
}

inline uint16_t shs::crc_16(const uint8_t *ptr, uint16_t size)
{

    uint16_t crc = 0xFFFF;

    while (size--)
    {
        shs::crc_16_update(crc, *ptr++);
    }
    return crc;
}

inline void shs::crc_32_update(uint32_t &crc, uint8_t data)
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

inline uint32_t shs::crc_32(const uint8_t *ptr, uint16_t size)
{
    uint32_t crc = 0; // 0xFFFFFFFF;
    while (size--)
    {
        shs::crc_32_update(crc, *ptr++);
    }
    return crc; // ^ 0xFFFFFFFF;
}
