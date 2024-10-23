#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/

#include <stdint.h>
#include <stddef.h>

#include "shs_settings_private.h"

#ifndef SHS_SF_UNUSE_STL
#include <algorithm>
#endif

namespace shs
{
    template <typename BCbuf_t>
    class ByteCollectorIterator;

    template <typename BCbuf_t, typename BCsize_t>
    class ByteCollectorReadIterator;
};


template <typename BCbuf_t = uint8_t>
class shs::ByteCollectorIterator
{
    static_assert(sizeof(BCbuf_t) == 1);
public:
    explicit ByteCollectorIterator(BCbuf_t* ptr) : m_ptr(ptr) {}
    ~ByteCollectorIterator() = default;

    shs::ByteCollectorIterator<BCbuf_t>& operator++()
    {
        m_ptr++;
        return *this;
    }

    BCbuf_t& operator*() { return *m_ptr; }
    BCbuf_t* operator&() { return m_ptr; }
    BCbuf_t& operator[](const size_t i) { return *(m_ptr + i); }

    bool operator!=(const shs::ByteCollectorIterator<BCbuf_t>& other) const { return m_ptr != other.m_ptr; }
    bool operator!=(const size_t ptr) const { return m_ptr != ptr; }
    bool operator!=(const BCbuf_t* ptr) const { return m_ptr != ptr; }

    bool operator==(const shs::ByteCollectorIterator<BCbuf_t>& other) const { return !(m_ptr != other.m_ptr); }
    bool operator==(const size_t ptr) const { return !(m_ptr != ptr); }
    bool operator==(const BCbuf_t* ptr) const { return !(m_ptr != ptr); }

protected:
    BCbuf_t* m_ptr{};
};

template <typename BCbuf_t>
size_t operator-(const shs::ByteCollectorIterator<BCbuf_t>& right, const shs::ByteCollectorIterator<BCbuf_t>& left)
{
    return static_cast<size_t>(right.m_ptr - left.m_ptr);
}


template <typename BCbuf_t = uint8_t, typename BCsize_t = uint8_t>
class shs::ByteCollectorReadIterator : public shs::ByteCollectorIterator<BCbuf_t>
{
    static_assert(sizeof(BCbuf_t) == 1);
public:
    explicit ByteCollectorReadIterator(const BCbuf_t* begin, const BCbuf_t* end, BCbuf_t* read_ptr)
        : ByteCollectorIterator<BCbuf_t>(read_ptr), m_begin(begin), m_end(end) {}

    ~ByteCollectorReadIterator() = default;

    template <typename T>
    BCsize_t get(T& var, BCsize_t bytes = sizeof(T))
    {
        if (m_end - this->m_ptr < bytes) bytes = m_end - this->m_ptr;
        for (BCsize_t i = 0; i < bytes; i++) *((BCbuf_t*)&var + i) = *this->m_ptr++;
        return bytes;
    }

    BCbuf_t read() { return this->m_ptr < m_end ? *(this->m_ptr++) : *(this->m_ptr - 1); }
    const BCbuf_t& operator[](const BCsize_t index) const { return m_begin[index]; }
    BCbuf_t& back() { return const_cast<BCbuf_t&>(*(m_end - 1)); }

    BCsize_t size() const { return m_end - m_begin; }

    const BCbuf_t* getPtr() const { return m_begin; }

    bool set_position(const BCsize_t pos)
    {
        if (m_end - m_begin < pos) return 0;
        this->m_ptr = (BCbuf_t*)(m_begin + pos);
        return 1;
    }

    shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t>& operator++()
    {
        this->m_ptr++;
        return *this;
    }

    shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> operator++(int)
    {
        shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> temp = *this;
        ++(*this);
        return temp;
    }



private:
    const BCbuf_t* m_begin;
    const BCbuf_t* m_end;

};


#ifndef SHS_SF_UNUSE_STL 
namespace std
{
    template <typename BCsize_t>
    struct iterator_traits<shs::ByteCollectorIterator<BCsize_t>>
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type = BCsize_t;
        using pointer = BCsize_t*;
        using reference = BCsize_t&;
        using difference_type = size_t;
    };
};
#endif
