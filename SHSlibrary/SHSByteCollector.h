#pragma once

namespace shs
{
    class ByteCollector;
};

class shs::ByteCollector
{
public:
    uint8_t *buf{};     // array
    uint8_t *ptr{};     // current position
    uint8_t *readPtr{}; // read position

    explicit ByteCollector(uint8_t size) : buf(new uint8_t[size]{}),
                                           ptr(buf), readPtr(buf),
                                           _size(size)
    {
    }

    ~ByteCollector()
    {
        delete[] buf;
    }

    /*
      The bytes argument specifies how many bytes 
      to write from the passed type.
      
      int value = 1000;
      bc.add(value, 2);  // will add 2 bytes
      bc.size();         // will return 2, not 4!

      bc.add(value);     // will add sizeof(value)
      bc.size();         // will return 6

    */
    // add to the end
    template <typename T>
    void add(const T &value, uint8_t bytes = sizeof(T))
    {
        if (_size - (ptr - buf) < bytes)
            reserve(bytes - (_size - (ptr - buf)));

        uint8_t *_ptr = (uint8_t *)&(value);
        for (uint8_t i = 0; i < bytes; i++)
            *ptr++ = *_ptr++;
    }

    // add to the beginning
    template <typename T>
    void addBefore(const T &value, uint8_t bytes = sizeof(T))
    {
        if (!_beforeSize)
            reserveBefore(bytes);
        if (_beforeSize - (_ptrBefore - buf) < bytes)
            reserveBefore(bytes);
        uint8_t *_ptr = (uint8_t *)&value;
        for (uint8_t i = 0; i < bytes; i++)
            *_ptrBefore++ = *_ptr++;
    }

    // unpack data
    template <typename T>
    void get(T &var, uint8_t bytes = sizeof(T))
    {
        uint8_t *_ptr = (uint8_t *)&var;
        for (uint8_t i = 0; i < bytes; i++)
            *_ptr++ = *readPtr++;
    }

    // reserve bytes for more size
    void reserve(uint8_t size)
    {
        if (!size)
            return;

        _size += size;
        uint8_t *n_buf = new uint8_t[_size]{};
        for (uint16_t i = 0; i < (ptr - buf); i++)
            n_buf[i] = buf[i];

        ptr = n_buf + (ptr - buf);
        _ptrBefore = n_buf + (_ptrBefore - buf);
        delete[] buf;
        buf = n_buf;
    }

    void reserveBefore(uint8_t size)
    {
        if (!size)
            return;
        _size += size;
        _beforeSize = size;
        uint8_t *n_buf = new uint8_t[_size]{};
        for (uint16_t i = size - 1; i < (ptr - buf) + size; i++)
            n_buf[i] = buf[i - size];

        ptr = n_buf + size + (ptr - buf);
        delete[] buf;
        buf = n_buf;
        _ptrBefore = buf;
        readPtr = buf;
    }

    uint16_t size()
    {
        return static_cast<uint16_t>(ptr - buf);
    }

private:
    uint16_t _size{};
    uint16_t _beforeSize{};
    uint8_t *_ptrBefore{};
};
