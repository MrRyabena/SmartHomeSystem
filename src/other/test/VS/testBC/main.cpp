#include <iostream>
#define LIB 0

#if (LIB == 0)
#include "..\..\..\ByteCollector.h"
#else
#include "..\..\BC.h"
#endif

int main()
{

    shs::ByteCollector c(32);

    uint8_t val1 = 25;
    uint16_t val2 = 1028;
    int64_t val3 = INT64_MAX;

    c.add(val1);
    c.add(val2);
    c.add(val3);
    c.add(34);

    std::cout << static_cast<int>(c.buf[0]) << ' ';
    std::cout << static_cast<int>(c.buf[1 + 2 + 8]) << std::endl;
    std::cout << c.size() << std::endl;

    c.reserveBefore(3);
    std::cout << c.size() << std::endl;
    // c.buf[0] = 2;
    c.addBefore(2, 1);
    c.addBefore(1111, 2);
    c.addBefore(4444, 2);
    std::cout << c.size() << std::endl;

    std::cout << (((uint16_t)c.buf[1] << 8) + c.buf[0]) << ' ';
    std::cout << static_cast<int>(c.buf[5]) << ' ';
    std::cout << (((uint16_t)c.buf[4] << 8) + c.buf[3]) << std::endl;
    std::cout << static_cast<int>(c.buf[0 + 5]) << ' ';
    std::cout << static_cast<int>(c.buf[1 + 2 + 8 + 5]) << std::endl;

    return 0;
}