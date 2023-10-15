#include <iostream>
#include "func.h"

#define LIB 0

#if (LIB == 0)
#include "..\ByteCollector.h"
#else
#include "BC.h"
#endif

int main() {

    ByteCollector c(32);


    uint8_t val1 = 25;
    uint16_t val2 = 1028;
    int64_t val3 = INT64_MAX;

    c.add(val1);
    c.add(val2);
    c.add(val3);
    c.addVal<uint8_t>(34);

    std::cout << static_cast<int>(c.buf[0]) << ' ';
    std::cout << static_cast<int>(c.buf[1 + 2 + 8]) << std::endl;
    std::cout << c.size() << std::endl;
    std::cout << static_cast<int>(*(c.ptr - 1)) << std::endl;

    //std::cout << "\n\n";

    ByteCollector col(10);

    uint32_t v1 = 1000;
    uint16_t v2 = 19;
    uint64_t v3 = 5;
    col.add(v1, 2);  // 0 1
    col.add(v2, 1);  // 2
    col.add(v3, 1);  // 3
    col.addVal<uint8_t>(10); // 4

    std::cout << "col" << std::endl;
    std::cout << static_cast<int>(col.size()) << std::endl;
    std::cout << (int)(col.buf[0] | (col.buf[1] << 8)) << std::endl;
    std::cout << static_cast<unsigned int>(col.buf[2]) << std::endl;
    std::cout << static_cast<unsigned int>(col.buf[3]) << std::endl;
    std::cout << static_cast<unsigned int>(col.buf[4]) << std::endl;

    func(col.buf);



    return 0;
}