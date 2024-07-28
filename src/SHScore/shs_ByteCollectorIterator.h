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
};


template <typename BCbuf_t = uint8_t>
class shs::ByteCollectorIterator
{
    static_assert(sizeof(BCbuf_t) == 1);
public:
    explicit ByteCollectorIterator(BCbuf_t *ptr) : m_ptr(ptr) {}
    ~ByteCollectorIterator() = default;

    shs::ByteCollectorIterator<BCbuf_t> &operator++()
    {
        m_ptr++;
        return *this;
    }

    BCbuf_t &operator*() { return *m_ptr; }
    BCbuf_t *operator&() { return m_ptr; }
    BCbuf_t &operator[](const size_t i) { return *(m_ptr + i); }

    bool operator!=(const shs::ByteCollectorIterator<BCbuf_t> &other) const
    {
        return m_ptr != other.m_ptr;
    }

    bool operator!=(const size_t ptr) const
    {
        return m_ptr != ptr;
    }

    bool operator!=(const BCbuf_t *ptr) const
    {
        return m_ptr != ptr;
    }

    bool operator==(const shs::ByteCollectorIterator<BCbuf_t> &other) const
    {
        return !(m_ptr != other.m_ptr);
    }

    bool operator==(const size_t ptr) const
    {
        return !(m_ptr != ptr);
    }

    bool operator==(const BCbuf_t *ptr) const
    {
        return !(m_ptr != ptr);
    }

private:
    BCbuf_t *m_ptr{};
};

template <typename BCbuf_t>
size_t operator-(const shs::ByteCollectorIterator<BCbuf_t> &right, const shs::ByteCollectorIterator<BCbuf_t> &left)
{
    return static_cast<size_t>(right.m_ptr - left.m_ptr);
}

#ifndef SHS_SF_UNUSE_STL
namespace std
{
    template <typename BCsize_t>
    struct iterator_traits<shs::ByteCollectorIterator<BCsize_t>>
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type = BCsize_t;
        using pointer = BCsize_t *;
        using reference = BCsize_t &;
        using difference_type = size_t;
    };
};
#endif

