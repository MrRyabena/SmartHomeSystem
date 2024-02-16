#pragma once
#include <stdint.h>

namespace shs
{
    template <typename T>
    class vector;
};

template <typename T, typename Size_T = size_t>
class vector
{
public:
    T *buf{};
    explicit vector(Size_T size = 1) : buf(new T(size){}), m_size(size) {}
    ~vector()
    {
        if (buf)
            delete[] buf;
    }

    void push_back(const T &value);
    void reserve(Size_T size);
    void clear();
    void shrink_to_fit();

    T *begin();
    T *end();

    T &front();
    T &back();

private:
    Size_T m_size{};
    Size_T m_capacity{};

public:
    void push_back(const T &value)
    {
        if (!m_capacity)
            reserve(1);

        buf[size++] = value;
    }

    void reserve(Size_T size)
    {
        if (!size)
            return;

        T *nbuf = new T(m_size + size){};
        for (Size_T i = 0; i < m_size; i++)
            nbuf[i] = buf[i];

        m_size += size;
        m_capacity += size;

        delete[] buf;
        buf = nbuf;
    }

    // template <typename T, typename Size_T = size_t>
    // T *shs::vector::begin() { return buf; }

    // template <typename T, typename Size_T = size_t>
    // T *shs::vector::end() { return (&buf[size] + 1); }

    void clear()
    {
        for (Size_T i = 0; i < m_size; i++)
            buf[i]{};
        m_size = 0;
    }

    void shrink_to_fit()
    {
        if (!m_capacity)
            return;

        T *nbuf = new T(size){};
        for (Size_T i = 0; i < m_size; i++)
            nbuf[i] = buf[i];

        m_capacity = 0;
        delete[] buf;
        buf = nbuf;
    }

    T &front() { return buf[0]; }

    T &back() { return buf[size - 1]; }
};
