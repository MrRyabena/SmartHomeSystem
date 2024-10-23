#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — edited and optimized.
    v1.0.0 — release.
    v1.1.0 — added a default value for size in the constructor.
           — fixed a critical error in functions get() and reserve().
    v2.0.0 — optimized.
           — changed function-member reserve_front().
           — added operator +=.
           — added BCbuf_t and BCsize_t.
           — added begin() and end().
           — renamed functions, added push_front, push_back, write and read.
           — added insert().
           — added move semantics.
           — added iterator.
*/

/*
  This is a lightweight class for packing and unpacking data into a byte array.
  You can specify the number of bytes to be add/get to save memory or align data types.
  The class is used in data transfer protocols.
*/

#include <stdint.h>

#include "shs_ByteCollectorIterator.h"

namespace shs
{
    template <typename BCbuf_t, typename BCsize_t>
    class ByteCollector;
};

template <typename BCbuf_t = uint8_t, typename BCsize_t = uint8_t>
class shs::ByteCollector
{
    static_assert(sizeof(BCbuf_t) == 1);
public:
    explicit ByteCollector(BCsize_t size = 0)
        : m_buf(new BCbuf_t[size]{}), m_capacity(size)
    {}

    ByteCollector(ByteCollector<BCbuf_t, BCsize_t>&& other) noexcept
        : m_buf(other.m_buf), m_capacity(other.m_capacity),
        m_pos_back(other.m_pos_back), m_pos_front(other.m_pos_front),
        m_pos_read(other.m_pos_read)
    {

        other.m_buf = nullptr;
        other.m_capacity = {};
        other.m_pos_back = {};
        other.m_pos_front = {};
        other.m_pos_read = {};
    }

    ByteCollector(const ByteCollector<BCbuf_t, BCsize_t>&) = delete;
    ByteCollector<BCbuf_t, BCsize_t>& operator=(const ByteCollector<BCbuf_t, BCsize_t>&) = delete;

    ~ByteCollector() { delete[] m_buf; }

    /*
      The bytes argument specifies how many bytes
      to write from the passed type.

      int value = 1000;       // note: sizeof(int) = 4 bytes
      bc.add_back(value, 2);  // will add 2 bytes
      bc.size();              // will return 2, not 4!

      bc.add_back(value);     // will add sizeof(value)
      bc.size();              // will return 6

    */

    void write(const BCbuf_t* begin, const BCsize_t size)
    {
        if (capacity_back() < size) reserve(size - capacity_back());
        for (BCsize_t i = 0; i < size; i++) m_buf[m_pos_back++] = begin[i];
    }

    // add to the end
    template <typename T>
    void push_back(const T& value, const BCsize_t bytes = sizeof(T)) { write((BCbuf_t*)&value, bytes); }


    // add to the beginning
    template <typename T>
    void push_front(const T& value, const BCsize_t bytes = sizeof(T))
    {
        if (capacity_front() < bytes) reserve_front(bytes - capacity_front());

        m_pos_front -= bytes;
        BCbuf_t* data_ptr = (BCbuf_t*)&value;
        for (BCsize_t i = 0; i < bytes; i++) m_buf[m_pos_front + i] = *data_ptr++;
    }

    void insert(const BCbuf_t* ptr, const BCsize_t size, const BCsize_t position)
    {
        m_capacity += size;
        BCbuf_t* n_buf = new BCbuf_t[m_capacity];

        BCsize_t i = m_pos_front;
        for (i; i < position; i++) n_buf[i] = m_buf[i];
        for (BCsize_t j = 0; j < size; j++) n_buf[i + j] = ptr[j];
        for (i; i < m_pos_back; i++) n_buf[i + size] = m_buf[i];

        delete[] m_buf;
        m_buf = n_buf;

        m_pos_back += size;
    }

    template <typename T>
    void insert(const T& value, const BCsize_t size, const BCsize_t position) { insert((const BCbuf_t*)&value, size, position); }

    // unpack data

    void read(BCbuf_t* begin, const BCsize_t size)
    {
        for (BCsize_t i = 0; i < size; i++) begin[i] = m_buf[m_pos_read++];
    }

    template <typename T>
    void get(T& var, const BCsize_t bytes = sizeof(T)) { read((BCbuf_t*)&var, bytes); }

    // reserve bytes for more size
    void reserve(const BCsize_t size)
    {
        if (!size) return;

        m_capacity += size;

        BCbuf_t* n_buf = new BCbuf_t[m_capacity]{};

        for (BCsize_t i = m_pos_front; i < m_pos_back; i++) n_buf[i] = m_buf[i];

        delete[] m_buf;
        m_buf = n_buf;
    }

    void reserve_front(const BCsize_t size)
    {
        if (!size) return;

        m_capacity += size;

        BCbuf_t* n_buf = new BCbuf_t[m_capacity]{};

        for (BCsize_t i = m_pos_front; i < m_pos_back; i++) n_buf[i + size] = m_buf[i];

        m_pos_back += size;
        m_pos_front += size;

        delete[] m_buf;
        m_buf = n_buf;
    }


    BCsize_t capacity_front() const { return m_pos_front; }
    BCsize_t capacity_back() const { return m_capacity - m_pos_back; }

    void shrink_to_fit()
    {
        if (!capacity_back() && !capacity_front()) return;

        m_capacity = size();
        BCbuf_t* n_buf = new BCbuf_t[m_capacity]{};

        for (BCsize_t i = m_pos_front; i < m_pos_back; i++) n_buf[i - m_pos_front] = m_buf[i];

        delete[] m_buf;
        m_buf = n_buf;

        m_pos_back = m_capacity;
        m_pos_front = 0;
    }

    void reset()
    {
        m_pos_back = 0;
        m_pos_front = 0;
        m_pos_read = 0;
    }

    void clear()
    {
        for (auto& x : *this) x = 0;
        reset();
    }

    BCbuf_t* getPtr() const { return m_buf; }
    shs::ByteCollectorIterator<BCbuf_t> begin() const { return shs::ByteCollectorIterator<BCbuf_t>(m_buf + m_pos_front); }
    shs::ByteCollectorIterator<BCbuf_t> end() const { return shs::ByteCollectorIterator<BCbuf_t>(m_buf + m_pos_back + 1); }
    BCsize_t size() const { return m_pos_back - m_pos_front; }
    BCbuf_t& back() const { return m_buf[m_pos_back]; }
    bool empty() const { return size() == 0; }

    const BCbuf_t& operator[](const BCsize_t index) const { return m_buf[index]; }

    BCsize_t getPositionBack() const { return m_pos_back; }
    BCsize_t getPostitionFront() const { return m_pos_front; }
    BCsize_t getPositionRead() const { return m_pos_read; }

    shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> getReadIt(const bool set_begin = false) const { return shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t>(m_buf, m_buf + m_pos_back, set_begin ? m_buf : (m_buf + m_pos_read)); }

    BCbuf_t setPositionBack(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_back = position;
        return 1;
    }

    BCbuf_t setPositionFront(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_front = position;
        return 1;
    }

    BCbuf_t setPositionRead(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_read = position;
        return 1;
    }


    template <typename T>
    shs::ByteCollector<BCbuf_t, BCsize_t>& operator+=(const T& other)
    {
        push_back(other);
        return *this;
    }


private:
    BCbuf_t* m_buf{};          // array

    BCsize_t m_capacity{};     // allocated size

    BCsize_t m_pos_back{};     // current position in back
    BCsize_t m_pos_front{};    // current position in front
    BCsize_t m_pos_read{};     // read position
};
