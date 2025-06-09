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



#include <stdint.h>

#include "shs_ByteCollectorIterator.h"

namespace shs
{
    template <typename BCbuf_t, typename BCsize_t>
    class ByteCollector;
};


/*
  @class shs::ByteCollector
  @brief A class for packing and unpacking data into a byte array.

  This class allows adding and retrieving data from a dynamically allocated byte array.
  You can specify the number of bytes to add or get to save memory or align data types.

  @tparam BCbuf_t The data type used for storing bytes (default is uint8_t).
  @tparam BCsize_t The data type used for representing size (default is uint8_t).

  @note The class is used in data transfer protocols and supports operations such as adding, inserting, reading, and clearing data.

  @version 2.2.0
  @date Last updated: v2.2.0
*/
template <typename BCbuf_t = uint8_t, typename BCsize_t = uint8_t>
class shs::ByteCollector
{
    static_assert(sizeof(BCbuf_t) == 1);
public:
    /*
      @brief Constructs a ByteCollector with a specified size.
      @param size The initial size of the byte buffer (default is 0).
    */
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
      @brief Writes a specified number of bytes from the provided buffer.
      @param begin Pointer to the buffer containing the data to write.
      @param size The number of bytes to write.
    */
    void write(const BCbuf_t* begin, const BCsize_t size)
    {
        if (capacity_back() < size) reserve(size - capacity_back());
        for (BCsize_t i = 0; i < size; i++) m_buf[m_pos_back++] = begin[i];
    }

    /*
      * @brief Adds data to the end of the byte array.
      * @tparam T The type of the value to add.
      * @param value The value to add.
      * @param bytes The number of bytes to add (default is the size of T).
      * @note The bytes argument specifies how many bytes to write from the passed type.
      *
      * @code{.cpp}
      * int value = 1000;       // note: sizeof(int) = 4 bytes
      *
      * bc.add_back(value, 2);  // will add 2 bytes
      *
      * bc.size();              // will return 2, not 4!
      *
      * bc.add_back(value);     // will add sizeof(value)
      *
      * bc.size();              // will return 6
      * @endcode
    */
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

    /*
      @brief Adds another ByteCollector to this one.
      @tparam T The type of the other ByteCollector.
      @param other The ByteCollector to add.
      @return A reference to this ByteCollector.
    */
    template <typename T>
    shs::ByteCollector<BCbuf_t, BCsize_t>& operator+=(const T& other)
    {
        push_back(other);
        return *this;
    }

    /*
      @brief Inserts data at a specified position in the byte array.
      @param ptr Pointer to the buffer containing the data to insert.
      @param size The number of bytes to insert.
      @param position The position at which to insert the data.
    */
    void insert(const BCbuf_t* ptr, const BCsize_t size, const BCsize_t position)
    {
        m_shift_right(position, size);

        for (BCsize_t i = 0; i < size; i++) m_buf[position + i] = ptr[i];
    }

    /*
      @brief Inserts a value at a specified position in the byte array.
      @tparam T The type of the value to insert.
      @param value The value to insert.
      @param size The number of bytes to insert.
      @param position The position at which to insert the value.
    */
    template <typename T>
    void insert(const T& value, const BCsize_t size, const BCsize_t position) { insert(reinterpret_cast<const BCbuf_t*>(&value), size, position); }

    /*
      @brief Reads a specified number of bytes into the provided buffer.
      @param begin Pointer to the buffer where the data will be read into.
      @param size The number of bytes to read.
    */
    void read(BCbuf_t* begin, const BCsize_t size)
    {
        for (BCsize_t i = 0; i < size; i++) begin[i] = m_buf[m_pos_read++];
    }

    /*
      @brief Retrieves a value from the byte array.
      @tparam T The type of the variable to retrieve.
      @param var The variable to store the retrieved value.
      @param bytes The number of bytes to read (default is the size of T).
    */
    template <typename T>
    void get(T& var, const BCsize_t bytes = sizeof(T)) { read(reinterpret_cast<BCbuf_t*>(&var), bytes); }

    /*
      @brief Accesses the element at a specified index.
      @param index The index of the element to access.
      @return A reference to the element at the specified index.
    */
    BCbuf_t& operator[](const BCsize_t index) const { return m_buf[index]; }

    /*
      @brief Reserves additional bytes at the end of the byte array.
      @param size The number of bytes to reserve.
    */
    void reserve(const BCsize_t size)
    {
        if (!size) return;

        m_capacity += size;

        BCbuf_t* n_buf = new BCbuf_t[m_capacity]{};

        for (BCsize_t i = m_pos_front; i < m_pos_back; i++) n_buf[i] = m_buf[i];

        delete[] m_buf;
        m_buf = n_buf;
    }

    /*
      @brief Reserves additional bytes at the beginning of the byte array.
      @param size The number of bytes to reserve.
    */
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

    /*
      @brief Gets the total capacity of the byte array.
      @return The total capacity.
    */
    BCsize_t capacity() const { return m_capacity; }

    /*
      @brief Gets the available capacity at the front of the byte array.
      @return The available capacity at the front.
    */
    BCsize_t capacity_front() const { return m_pos_front; }

    /*
      @brief Gets the available capacity at the back of the byte array.
      @return The available capacity at the back.
    */
    BCsize_t capacity_back() const { return m_capacity - m_pos_back; }

    /*
      @brief Shrinks the capacity of the byte array to the size of the data.
    */
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

    /*
      @brief Shrinks the capacity of the byte array to the size of the read data.
      The read data will be deleted.
    */
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

    /*
      @brief Resets the data without clearing it (fast reset).
    */
    void reset()
    {
        m_pos_back = 0;
        m_pos_front = 0;
        m_pos_read = 0;
    }

    /*
      @brief Clears the data (buffer will be initialized with 0).
    */
    void clear()
    {
        for (auto& x : *this) x = 0;
        reset();
    }

    /*
      @brief Gets a pointer to the underlying buffer.
      @return A pointer to the buffer.
    */
    BCbuf_t* getPtr() const { return m_buf; }

    /*
      @brief Gets an iterator to the beginning of the data.
      @return An iterator to the beginning.
    */
    shs::ByteCollectorIterator<BCbuf_t> begin() const { return shs::ByteCollectorIterator<BCbuf_t>(m_buf + m_pos_front); }

    /*
      @brief Gets an iterator to the end of the data.
      @return An iterator to the end.
    */
    shs::ByteCollectorIterator<BCbuf_t> end() const { return shs::ByteCollectorIterator<BCbuf_t>(m_buf + m_pos_back + 1); }

    /*
      @brief Gets the size of the data.
      @return The size of the data.
    */
    BCsize_t size() const { return m_pos_back - m_pos_front; }

    /*
      @brief Gets the last element of the data.
      @return A reference to the last element.
    */
    BCbuf_t& back() const { return m_buf[m_pos_back]; }

    /*
      @brief Checks if the data is empty.
      @return True if the data is empty, false otherwise.
    */
    bool empty() const { return size() == 0; }

    /*
      @brief Gets the size of the data available for reading.
      @return The size of the data available for reading.
    */
    BCsize_t readAvailable() const { return m_pos_back - m_pos_read; }

    /*
      @brief Gets the current position at the back of the data.
      @return The current position at the back.
    */
    BCsize_t getPositionBack() const { return m_pos_back; }

    /*
      @brief Gets the current position at the front of the data.
      @return The current position at the front.
    */
    BCsize_t getPositionFront() const { return m_pos_front; }

    /*
      @brief Gets the current position for reading the data.
      @return The current position for reading.
    */
    BCsize_t getPositionRead() const { return m_pos_read; }

    /*
      @brief Gets an iterator to the beginning of the data available for reading.
      @param set_begin If true, sets the iterator to the beginning.
      @return An iterator to the beginning of the data available for reading.
    */
    shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> getReadIt(const bool set_begin = false) const { return shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t>(m_buf, m_buf + m_pos_back, set_begin ? m_buf : (m_buf + m_pos_read)); }

    /*
      @brief Sets the position at the back of the data.
      @param position The position to set.
      @return 1 if successful, 0 if the position is out of bounds.
    */
    BCbuf_t setPositionBack(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_back = position;
        return 1;
    }

    /*
      @brief Sets the position at the front of the data.
      @param position The position to set.
      @return 1 if successful, 0 if the position is out of bounds.
    */
    BCbuf_t setPositionFront(const BCsize_t position)
    {
        if (position > m_capacity) return 0;
        m_pos_front = position;
        return 1;
    }

    /*
      @brief Sets the position for reading the data.
      @param position The position to set.
      @return 1 if successful, 0 if the position is out of bounds.
    */
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
