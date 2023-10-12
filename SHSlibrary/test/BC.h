#pragma once
#include <stdint.h>

class ByteCollector {
public:
    uint8_t* buf{};
    uint8_t* ptr{};

    // ByteCollector(uint8_t size): buf(new uint8_t[size]) {
    //     ptr = buf;
    // }

    ByteCollector(uint8_t size);

    ~ByteCollector(); 



    uint16_t size();


    template <typename T>
    void add(T& value, uint8_t bytes = sizeof(T));

    template <typename T>
    void addVal(T value, uint8_t bytes = sizeof(T));
};
