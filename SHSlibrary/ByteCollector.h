#pragma once


class ByteCollector {
public:
    uint8_t* buf{};
    uint8_t* ptr{};

    ByteCollector(uint8_t size): buf(new uint8_t[size]) {
      ptr = buf;
    }

    ~ByteCollector() {
        delete [] buf;
    }



    uint16_t size() {
        return static_cast<uint16_t>(ptr - buf);
    }


    template <typename T>
    void add(T& value, uint8_t bytes = sizeof(T)) {
        uint8_t* _ptr = (uint8_t*)&(value);
        _ptr += sizeof(T) - bytes;

        for (uint8_t i = 0; i < bytes; i++) *ptr++ = *_ptr++;

    }


    template <typename T>
    void addVal(T value, uint8_t bytes = sizeof(T)) {
        uint8_t* _ptr = (uint8_t*)&(value);
        _ptr += sizeof(T) - bytes;

        for (uint8_t i = 0; i < bytes; i++) *ptr++ = *_ptr++;

    }
};
