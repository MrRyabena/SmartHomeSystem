#include "BC.h"


ByteCollector::ByteCollector(uint8_t size): buf(new uint8_t[size]) {
    ptr = buf;
}

ByteCollector::~ByteCollector() {
    delete[] buf;
    // buf = nullptr;
    // ptr = nullptr;
}

uint16_t ByteCollector::size() {
    return static_cast<uint16_t>(ptr - buf);
}


template <typename T>
void ByteCollector::add(const T& value, uint8_t bytes = sizeof(T)) {
    uint8_t* _ptr = (uint8_t*)&(value);
    // _ptr += sizeof(T) - bytes;

    for (uint8_t i = 0; i < bytes; i++) *ptr++ = *_ptr++;

}


template <typename T>
void ByteCollector::addVal(const T value, uint8_t bytes = sizeof(T)) {
    uint8_t* _ptr = (uint8_t*)&(value);
    // _ptr += sizeof(T) - bytes;

    for (uint8_t i = 0; i < bytes; i++) *ptr++ = *_ptr++;

}