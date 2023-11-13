#pragma once

namespace shs
{
    class ByteCollector
    {
    public:
        uint8_t *buf{};
        uint8_t *ptr{};
        uint8_t *readPtr{};

        ByteCollector(uint8_t size) : buf(new uint8_t[size])
        {
            ptr = buf;
            readPtr = buf;
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

        void reserve(uint8_t size)
        {
            if (!size)
                return;

            _size += size;
            uint8_t *n_buf = new uint8_t[_size];
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
            uint8_t *n_buf = new uint8_t[_size];
            for (uint16_t i = size; i < (ptr - buf); i++)
                n_buf[i] = buf[i - size];

            ptr = n_buf + size + (ptr - buf);
            delete[] buf;
            buf = n_buf;
            _ptrBefore = buf;
            readPtr = buf;
        }

        template <typename T>
        void get(T &var, uint8_t bytes = sizeof(T))
        {
            uint8_t *_ptr = (uint8_t *)&var;
            for (uint8_t i = 0; i < bytes; i++)
                *_ptr++ = *readPtr++;
        }

    private:
        uint16_t _size{};
        uint16_t _beforeSize{};
        uint8_t *_ptrBefore{};
        };
};
