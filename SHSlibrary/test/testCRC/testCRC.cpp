#include <iostream>
#include "../../SHSalgoritm.h"
#include "text.h"

unsigned short crc16(const unsigned char *data_p, unsigned char length)
{
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (length--)
    {
        x = crc >> 8 ^ *data_p++;
        x ^= x >> 4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x << 5)) ^ ((unsigned short)x);
    }
    return crc;
}

uint32_t Fcrc_32(const uint8_t *ptr, uint16_t size)
{
    uint32_t crc = 0xFFFFFFFF;
    while (size--)
    {
        crc ^= *ptr++;
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc = (crc >> 1);
        }
    }
    return crc ^ 0xFFFFFFFF;
}

int main()
{
    const char *str = "Smart Home System";

    std::cout << static_cast<int>(shs::crc_8((uint8_t *)str, 18)) << '\n'
              << shs::crc_16((uint8_t *)str, 18) << '\n'
              << shs::crc_32((uint8_t *)str, 18) << '\n'
              << Fcrc_32((uint8_t *)str, 18) << '\n'
              << crc16((unsigned char *)str, 18) << '\n'
              << std::endl;
    /*
    58
    30550
    328699274
    */

    std::cout << static_cast<int>(shs::crc_8((uint8_t *)text, Tsize)) << '\n'
              << shs::crc_16((uint8_t *)text, Tsize) << '\n'
              << shs::crc_32((uint8_t *)text, Tsize) << std::endl;
    /*
    104
    42490
    2507306757
    */
    return 0;
}
