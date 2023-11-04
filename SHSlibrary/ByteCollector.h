#pragma once

class ByteCollector
{
public:
    uint8_t *buf{};
    uint8_t *ptr{};

    ByteCollector(uint8_t size) : buf(new uint8_t[size])
    {
        ptr = buf;
        _size = size;
    }

    ~ByteCollector()
    {
        delete[] buf;
    }

    uint16_t size()
    {
        return static_cast<uint16_t>(ptr - buf);
    }

    template <typename T>
    void add(const T &value, uint8_t bytes = sizeof(T))
    {
        if (_size - (ptr - buf) < bytes)
            reserve(bytes - (_size - (ptr - buf)));

        uint8_t *_ptr = (uint8_t *)&(value);
        for (uint8_t i = 0; i < bytes; i++)
            *ptr++ = *_ptr++;
    }

    void reserve(uint8_t size)
    {
        if (!size)
            return;

        _size += size;
        uint8_t *n_buf = new uint8_t[_size];
        for (uint16_t i = 0; i < (ptr - buf); i++)
            n_buf[i] = buf[i];

        ptr = n_buf + (ptr - buf);
        delete[] buf;
        buf = n_buf;
    }

private:
    uint16_t _size{};
};
