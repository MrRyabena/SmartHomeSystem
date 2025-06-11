# shs_ByteCollector.h

## General Description

This file contains the definition of the `shs::ByteCollector` class, which is a lightweight utility for packing and unpacking data into a byte array. It allows you to specify the number of bytes to add or get, optimizing memory usage and aligning data types. The class is primarily used in data transfer protocols.

## Versions

- **v0.1.0** — created.
- **v0.2.0** — edited and optimized.
- **v1.0.0** — release.
- **v1.1.0** — added a default value for size in the constructor; fixed a critical error in functions `get()` and `reserve()`.
- **v2.0.0** — optimized; changed function-member `reserve_front()`; added operator `+=`; added `BCbuf_t` and `BCsize_t`; added `begin()` and `end()`; renamed functions, added `push_front`, `push_back`, `write`, and `read`; added `insert()`; added move semantics; added iterator.

---

## Class `shs::ByteCollector`

### Description

`shs::ByteCollector` is a template class that provides functionality for managing a dynamic byte array. It supports various operations for adding, reading, and manipulating byte data.

### Template Parameters

`BCbuf_t` — type of the buffer used to store bytes. Default is `uint8_t`.
> [!IMPORTANT]
> sizeof(BCbut_t) must be 1 byte.

`BCsize_t`— type used for size representation. Default is `uint8_t`.

---

### Constructor

- ##### `ByteCollector(size)`

  ```cpp
  explicit ByteCollector(BCsize_t size = 0);
  ```

  - ##### Parameters

    - **size** — the initial size of the buffer. Default is `0`.

---

### Destructor

- ##### `~ByteCollector()`

  ```cpp
  ~ByteCollector();
  ```

  - Cleans up the allocated memory for the byte buffer.

---

### Methods

#### Write Operations

- ##### `void write(begin, size)`

  ```cpp
  void write(const BCbuf_t* begin, const BCsize_t size);
  ```

  - ##### Description

    Writes a specified number of bytes from the provided buffer to the end of the byte collector.

  - ##### Parameters

    - `begin` — pointer to the beginning of the data to write.
    - `size` — the number of bytes to write.

- ##### `void push_back(value, bytes)`

  ```cpp
  template <typename T> void push_back(const T& value, const BCsize_t bytes = sizeof(T));
  ```

  - ##### Description

    Adds a value to the end of the buffer. The number of bytes to write can be specified.

  - ##### Parameters

    - `value` — the value to add to the buffer.
    - `bytes` — the number of bytes to write (default is the size of `T`).

- ##### `void push_front(value, bytes)`

  ```cpp
  template <typename T> void push_front(const T& value, const BCsize_t bytes = sizeof(T));
  ```

  - ##### Description

    Adds a value to the beginning of the buffer. The number of bytes to write can be specified.

  - ##### Parameters

    - `value` — the value to add to the buffer.
    - `bytes` — the number of bytes to write (default is the size of `T`).

- ##### `void insert(ptr, size, position)`

  ```cpp
  void insert(const BCbuf_t* ptr, const BCsize_t size, const BCsize_t position);
  ```

  - ##### Description

    Inserts a specified number of bytes at a given position in the buffer.

  - ##### Parameters

    - `ptr` — pointer to the data to insert.
    - `size` — the number of bytes to insert.
    - `position` — the position at which to insert the data.

- ##### `void insert(value, size, position)`

  ```cpp
  template <typename T> void insert(const T& value, const BCsize_t size, const BCsize_t position);
  ```

  - ##### Description

    Inserts a value at a specified position in the buffer.

  - ##### Parameters

    - `value` — the value to insert.
    - `size` — the number of bytes to write.
    - `position` — the position at which to insert the value.

---

#### Read Operations

- ##### `void read(begin, size)`

  ```cpp
  void read(BCbuf_t* begin, const BCsize_t size);
  ```

  - ##### Description

    Reads a specified number of bytes from the buffer into the provided buffer.

  - ##### Parameters

    - `begin` — the beginning pointer of the range.
    - `size` — the size of the range.

- ##### `void get(var, bytes)`

  ```cpp
  template <typename T> void get(T& var, const BCsize_t bytes = sizeof(T));
  ```

  - ##### Description

    Retrieves a value from the buffer and stores it in the provided variable.

  - ##### Parameters

    - `var` — the variable to store the retrieved value.
    - `bytes` — the number of bytes to read (default is the size of `T`).

- ##### `BCbuf_t& back() const`

  ```cpp
  BCbuf_t& back() const;
  ```

  - ##### Description

    Returns a reference to the last byte in the byte collector.

---

#### Size Management

- ##### `void reserve(size)`

  ```cpp
  void reserve(const BCsize_t size);
  ```

  - ##### Description

    Reserves additional space in the buffer.

  - ##### Parameters

    - `size` — the amount of space to reserve.

- ##### `void reserve_front(size)`

  ```cpp
  void reserve_front(const BCsize_t size);
  ```

  - ##### Description

    Reserves additional space at the front of the buffer.

  - ##### Parameters

    - `size` — the amount of space to reserve at the front.

- ##### `BCsize_t capacity() const`

  ```cpp
  BCsize_t capacity() const;
  ```

  - ##### Description

    Returns the total allocated size of the buffer.

- ##### `BCsize_t capacity_front() const`

  ```cpp
  BCsize_t capacity_front() const;
  ```

  - ##### Description

    Returns the amount of space available at the front of the buffer.

- ##### `BCsize_t capacity_back() const`

  ```cpp
  BCsize_t capacity_back() const;
  ```

  - ##### Description

    Returns the amount of space available at the back of the buffer.

- ##### `BCsize_t size() const`

  ```cpp
  BCsize_t size() const;
  ```

  - ##### Description

    Returns the number of bytes currently stored in the buffer.

- ##### `void shrink_to_fit()`

  ```cpp
  void shrink_to_fit();
  ```

  - ##### Description

    Reduces the capacity of the buffer to fit its current size.

- ##### `void shrink_to_read()`

  ```cpp
  void shrink_to_read();
  ```

  - ##### Description

    Frees up memory from the portion of the buffer that has been read, reducing the size of the buffer to only include unread data.

---

#### Position Management

- ##### `BCsize_t setPositionBack(position)`

  ```cpp
  BCsize_t setPositionBack(const BCsize_t position);
  ```

  - ##### Description

    Sets the current position at the back of the buffer.

  - ##### Parameters

    - `position` — the position to set at the back.

- ##### `BCsize_t setPositionFront(position)`

  ```cpp
  BCsize_t setPositionFront(const BCsize_t position);
  ```

  - ##### Description

    Sets the current position at the front of the buffer.

  - ##### Parameters

    - `position` — the position to set at the front.

- ##### `BCsize_t setPositionRead(position)`

  ```cpp
  BCsize_t setPositionRead(const BCsize_t position);
  ```

  - ##### Description

    Sets the current read position in the buffer.

  - ##### Parameters

    - `position` — the position to set for reading.

- ##### `BCsize_t getPositionBack() const`

  ```cpp
  BCsize_t getPositionBack() const;
  ```

  - ##### Description

    Returns the current position at the back of the buffer.

- ##### `BCsize_t getPositionFront() const`

  ```cpp
  BCsize_t getPositionFront() const;
  ```

  - ##### Description

    Returns the current position at the front of the buffer.

- ##### `BCsize_t getPositionRead() const`

  ```cpp
  BCsize_t getPositionRead() const;
  ```

  - ##### Description

    Returns the current read position in the buffer.

---

#### Utility Functions

- ##### `bool empty() const`

  ```cpp
  bool empty() const;
  ```

  - ##### Description

    Checks if the buffer is empty.

- ##### `BCbuf_t* getPtr() const`

  ```cpp
  BCbuf_t* getPtr() const;
  ```

  - ##### Description

    Returns a pointer to the underlying byte buffer.

- ##### `shs::ByteCollectorIterator<BCbuf_t> begin() const`

  ```cpp
  shs::ByteCollectorIterator<BCbuf_t> begin() const;
  ```

  - ##### Description

    Returns an iterator to the beginning of the buffer.

- ##### `shs::ByteCollectorIterator<BCbuf_t> end() const`

  ```cpp
  shs::ByteCollectorIterator<BCbuf_t> end() const;
  ```

  - ##### Description

    Returns an iterator to the end of the buffer.

- ##### `BCbuf_t& operator[](index)`

  ```cpp
  BCbuf_t& operator[](const BCsize_t index) const;
  ```

  - ##### Description

    Accesses the byte at the specified index in the buffer.

- ##### `void reset()`

  ```cpp
  void reset();
  ```

  - ##### Description

    Resets the positions in the buffer to zero.

- ##### `void clear()`

  ```cpp
  void clear();
  ```

  - ##### Description

    Clears the contents of the buffer and resets its positions.

- ##### `BCsize_t readAvailable() const`

  ```cpp
  BCsize_t readAvailable() const;
  ```

  - ##### Description

    Returns the number of bytes available for reading in the buffer.

- ##### `shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> getReadIt(set_begin)`

  ```cpp
  shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> getReadIt(const bool set_begin = false) const;
  ```

  - ##### Description

    Returns a read iterator for the buffer, optionally setting the beginning position.

---

#### Operators

- ##### `BCbuf_t& operator[](index)`

  ```cpp
  BCbuf_t& operator[](const BCsize_t index) const;
  ```

  - ##### Description

    Accesses the byte at the specified index in the buffer.

- ##### `shs::ByteCollector<BCbuf_t, BCsize_t>& operator+=(other)`

  ```cpp
  shs::ByteCollector<BCbuf_t, BCsize_t>& operator+=(const T& other);
  ```

  - ##### Description

    Adds a value to the byte collector.

---

### Example Usage

```cpp
shs::ByteCollector<> bc;
int value = 1000;

bc.push_back(value, 2);               // Adds 2 bytes of the integer value
bc.get(value, 2);
```

---

## Iterators

### Class `shs::ByteCollectorIterator`

#### Description

`shs::ByteCollectorIterator` is a template class that provides an iterator for traversing the byte collector.

#### Template Parameters

`BCbuf_t` — type of the buffer used to store bytes. Default is `uint8_t`.

#### Constructor

- ##### `ByteCollectorIterator(ptr)`

  ```cpp
  explicit ByteCollectorIterator(BCbuf_t* ptr);
  ```

  - ##### Parameters

    - **ptr** — pointer to the buffer to iterate over.

#### Methods

- ##### `operator++()`

  ```cpp
  shs::ByteCollectorIterator<BCbuf_t>& operator++();
  ```

  - ##### Description

    Increments the iterator to the next byte.

- ##### `operator*()`

  ```cpp
  BCbuf_t& operator*();
  ```

  - ##### Description

    Dereferences the iterator to access the current byte.

- ##### `operator&()`

  ```cpp
  BCbuf_t* operator&();
  ```

  - ##### Description

    Returns the pointer to the current byte.

- ##### `operator!=(other)`

  ```cpp
  bool operator!=(const shs::ByteCollectorIterator<BCbuf_t>& other) const;
  ```

  - ##### Description

    Checks if two iterators are not equal.

- ##### `operator==(other)`

  ```cpp
  bool operator==(const shs::ByteCollectorIterator<BCbuf_t>& other) const;
  ```

  - ##### Description

    Checks if two iterators are equal.

- ##### `operator-(right, left)`

  ```cpp
  size_t operator-(const shs::ByteCollectorIterator<BCbuf_t>& right, const shs::ByteCollectorIterator<BCbuf_t>& left);
  ```

  - ##### Description

    Calculates the distance between two iterators.

---

### Class `shs::ByteCollectorReadIterator`

#### Description

`shs::ByteCollectorReadIterator` is a template class that extends `shs::ByteCollectorIterator` to provide read functionality for the byte collector.

#### Template Parameters

`BCbuf_t` — type of the buffer used to store bytes. Default is `uint8_t`.

`BCsize_t` — type used for size representation. Default is `uint8_t`.

#### Constructor

- ##### `ByteCollectorReadIterator(begin, end, read_ptr)`

  ```cpp
  explicit ByteCollectorReadIterator(const BCbuf_t* begin, const BCbuf_t* end, BCbuf_t* read_ptr);
  ```

  - ##### Parameters

    - **begin** — pointer to the start of the buffer.
    - **end** — pointer to the end of the buffer.
    - **read_ptr** — pointer to the current read position.

#### Methods

- ##### `get(var, bytes)`

  ```cpp
  template <typename T> BCsize_t get(T& var, BCsize_t bytes = sizeof(T));
  ```

  - ##### Description

    Retrieves a specified number of bytes from the iterator into the provided variable.

  - ##### Parameters

    - `var` — the variable to store the retrieved value.
    - `bytes` — the number of bytes to read (default is the size of `T`).

- ##### `BCbuf_t read()`

  ```cpp
  BCbuf_t read();
  ```

  - ##### Description

    Reads the next byte from the iterator.

- ##### `operator[](index)`

  ```cpp
  const BCbuf_t& operator[](const BCsize_t index) const;
  ```

  - ##### Description

    Accesses the byte at the specified index in the read iterator.

- ##### `BCsize_t size()`

  ```cpp
  BCsize_t size() const;
  ```

  - ##### Description

    Returns the number of bytes available for reading.

- ##### `BCbuf_t* getPtr()`

  ```cpp
  const BCbuf_t* getPtr() const;
  ```

  - ##### Description

    Returns a pointer to the beginning of the read buffer.
