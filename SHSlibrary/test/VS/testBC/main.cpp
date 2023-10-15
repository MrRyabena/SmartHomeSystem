#include <iostream>
#define LIB 1

#if (LIB == 0)
#include "..\..\..\ByteCollector.h"
#else
#include "..\..\BC.h"
#endif

int main() {

    ByteCollector c(32);

    uint8_t val1 = 25;
    uint16_t val2 = 1028;
    int64_t val3 = INT64_MAX;

    c.add(val1);
    c.add(val2);
    c.add(val3);
    c.addVal(34);

    std::cout << static_cast<int>(c.buf[0]) << ' ';
    std::cout << static_cast<int>(c.buf[1 + 2 + 8]) << std::endl;


    return 0;
}