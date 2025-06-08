#pragma once

/*
  Last update: v2.1.0
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
    v2.1.0 — memory optimization.
    v2.2.0 — optimized.
           - removed c-style casts.
           - added private functions m_shift_right() and m_shift_left().
           - optimized insert().
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
    explicit ByteCollector(BCsize_t size = 0) noexcept : m_buf(size ? new BCbuf_t[size]{} : nullptr), m_capacity(size)
    {}

    ByteCollector(const ByteCollector<BCbuf_t, BCsize_t>& other) noexcept
        : m_buf(other.m_capacity ? new BCbuf_t[other.m_capacity] : nullptr),
        m_capacity(other.m_capacity),
        m_pos_back(other.m_pos_back),
        m_pos_front(other.m_pos_front),
        m_pos_read(other.m_pos_read)
    {
        if (m_buf && other.m_buf)
        {
            for (BCsize_t i = 0; i < m_capacity; i++) m_buf[i] = other.m_buf[i];
        }
    }

    ByteCollector(ByteCollector<BCbuf_t, BCsize_t>&& other) noexcept
        : m_buf(other.m_buf),
        m_capacity(other.m_capacity),
        m_pos_back(other.m_pos_back),
        m_pos_front(other.m_pos_front),
        m_pos_read(other.m_pos_read)
    {
        other.m_buf = nullptr;
        other.m_capacity = 0;
        other.m_pos_back = 0;
        other.m_pos_front = 0;
        other.m_pos_read = 0;
    }

    ByteCollector& operator=(const ByteCollector<BCbuf_t, BCsize_t>& other) noexcept
    {
        if (this != &other)
        {
            if (m_buf) delete[] m_buf;
            m_buf = nullptr;

            m_capacity = other.m_capacity;
            m_pos_back = other.m_pos_back;
            m_pos_front = other.m_pos_front;
            m_pos_read = other.m_pos_read;

            if (m_capacity)
            {
                m_buf = new BCbuf_t[m_capacity];
                if (m_buf && other.m_buf)
                {
                    for (BCsize_t i = 0; i < m_capacity; i++) m_buf[i] = other.m_buf[i];
                }
            }
        }
        return *this;
    }

    ByteCollector& operator=(ByteCollector<BCbuf_t, BCsize_t>&& other) noexcept
    {
        if (this != &other)
        {
            if (m_buf) delete[] m_buf;

            m_buf = other.m_buf;
            m_capacity = other.m_capacity;
            m_pos_back = other.m_pos_back;
            m_pos_front = other.m_pos_front;
            m_pos_read = other.m_pos_read;

            other.m_buf = nullptr;
            other.m_capacity = 0;
            other.m_pos_back = 0;
            other.m_pos_front = 0;
            other.m_pos_read = 0;
        }
        return *this;
    }


    ~ByteCollector() { if (m_buf) delete[] m_buf; }

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

    // Add data to the end
    template <typename T>
    void push_back(const T& value, const BCsize_t bytes = sizeof(T)) { write(reinterpret_cast<const BCbuf_t*>(&value), bytes); }


    // Add data to the beginning
    template <typename T>
    void push_front(const T& value, const BCsize_t bytes = sizeof(T))
    {
        if (capacity_front() < bytes) reserve_front(bytes - capacity_front());

        m_pos_front -= bytes;
        BCbuf_t* data_ptr = reinterpret_cast<const BCbuf_t*>(&value);
        for (BCsize_t i = 0; i < bytes; i++) m_buf[m_pos_front + i] = *data_ptr++;
    }


    // Add data to the end
    template <typename T>
    shs::ByteCollector<BCbuf_t, BCsize_t>& operator+=(const T& other)
    {
        push_back(other);
        return *this;
    }


    // Insert data at the specified position
    void insert(const BCbuf_t* ptr, const BCsize_t size, const BCsize_t position)
    {
        m_shift_right(position, size);

        for (BCsize_t i = 0; i < size; i++) m_buf[position + i] = ptr[i];
    }

    // Insert data at the specified position
    template <typename T>
    void insert(const T& value, const BCsize_t size, const BCsize_t position) { insert(reinterpret_cast<const BCbuf_t*>(&value), size, position); }

    // Unpack data
    void read(BCbuf_t* begin, const BCsize_t size)
    {
        for (BCsize_t i = 0; i < size; i++) begin[i] = m_buf[m_pos_read++];
    }

    // Unpack data
    template <typename T>
    void get(T& var, const BCsize_t bytes = sizeof(T)) { read(reinterpret_cast<BCbuf_t*>(&var), bytes); }

    // Get the element at the specified index
    BCbuf_t& operator[](const BCsize_t index) const { return m_buf[index]; }

    // Reserve bytes for more size at the end
    void reserve(const BCsize_t size)
    {
        if (!size) return;

        m_capacity += size;

        BCbuf_t* n_buf = new BCbuf_t[m_capacity]{};

        for (BCsize_t i = m_pos_front; i < m_pos_back; i++) n_buf[i] = m_buf[i];

        delete[] m_buf;
        m_buf = n_buf;
    }

    // Reserve bytes for more size at the beginning
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


    BCsize_t capacity() const { return m_capacity; }
    BCsize_t capacity_front() const { return m_pos_front; }
    BCsize_t capacity_back() const { return m_capacity - m_pos_back; }

    // Shrink the capacity to the size of the data
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

    // Shrink the capacity to the size of the read data. The read data will be deleted.
    void shrink_to_read()
    {
        if (m_pos_read == 0) return;
        m_capacity = size() - m_pos_read;

        BCbuf_t* n_buf = new BCbuf_t[m_capacity]{};
        for (BCsize_t i = m_pos_read; i < m_pos_back; i++) n_buf[i - m_pos_read] = m_buf[i];

        delete[] m_buf;
        m_buf = n_buf;

        m_pos_back = m_capacity;
        m_pos_front = 0;
        m_pos_read = 0;
    }

    // Reset the data, but not clear it (fast reset)
    void reset()
    {
        m_pos_back = 0;
        m_pos_front = 0;
        m_pos_read = 0;
    }

    // Clear the data (buffer will be initialized with 0)
    void clear()
    {
        for (auto& x : *this) x = 0;
        reset();
    }

    // Get the pointer to the buffer
    BCbuf_t* getPtr() const { return m_buf; }

    // Get the iterator to the beginning of the data
    shs::ByteCollectorIterator<BCbuf_t> begin() const { return shs::ByteCollectorIterator<BCbuf_t>(m_buf + m_pos_front); }

    // Get the iterator to the end of the data
    shs::ByteCollectorIterator<BCbuf_t> end() const { return shs::ByteCollectorIterator<BCbuf_t>(m_buf + m_pos_back + 1); }

    // Get the size of the data
    BCsize_t size() const { return m_pos_back - m_pos_front; }

    // Get the last element of the data
    BCbuf_t& back() const { return m_buf[m_pos_back]; }

    // Check if the data is empty
    bool empty() const { return size() == 0; }

    // Get the size of the data available for reading
    BCsize_t readAvailable() const { return m_pos_back - m_pos_read; }

    BCsize_t getPositionBack() const { return m_pos_back; }
    BCsize_t getPositionFront() const { return m_pos_front; }
    BCsize_t getPositionRead() const { return m_pos_read; }

    // Get the iterator to the beginning of the data available for reading
    shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> getReadIt(const bool set_begin = false) const { return shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t>(m_buf, m_buf + m_pos_back, set_begin ? m_buf : (m_buf + m_pos_read)); }

    // Set the position of the data at the end
    BCbuf_t setPositionBack(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_back = position;
        return 1;
    }

    // Set the position of the data at the front
    BCbuf_t setPositionFront(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_front = position;
        return 1;
    }

    // Set the position of the data available for reading
    BCbuf_t setPositionRead(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_read = position;
        return 1;
    }

private:
    BCbuf_t* m_buf{};          // array

    BCsize_t m_capacity{};     // allocated size

    BCsize_t m_pos_back{};     // current position in back
    BCsize_t m_pos_front{};    // current position in front
    BCsize_t m_pos_read{};     // read position


    void m_shift_right(const BCsize_t start_position, const BCsize_t size)
    {
        if (start_position > m_pos_back) return;
        if (size > capacity_back()) reserve(size - capacity_back());

        for (BCsize_t i = m_pos_back; i > position; i--) m_buf[i + size] = m_buf[i];
        m_pos_back += size;
    }

    void m_shift_left(const BCsize_t start_position, const BCsize_t size)
    {
        if (start_position > m_pos_back) return;
        if (size < capacity_front()) reserve_front(capacity_front() - size);

        for (BCsize_t i = position; i < m_pos_back; i++) m_buf[i - size] = m_buf[i];
        m_pos_back -= size;
    }
};
