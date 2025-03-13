# shs_ByteCollector.h

## General Description

This file contains the definition of the `shs::ByteCollector` class, which is a lightweight utility for packing and unpacking data into a byte array. It allows you to specify the number of bytes to add or get, optimizing memory usage and aligning data types. The class is primarily used in data transfer protocols.

## Versions

- **v0.1.0** — created.
- **v0.2.0** — edited and optimized.
- **v1.0.0** — release.
- **v1.1.0** — added a default value for size in the constructor; fixed a critical error in functions `get()` and `reserve()`.
- **v2.0.0** — optimized; changed function-member `reserve_front()`; added operator `+=`; added `BCbuf_t` and `BCsize_t`; added `begin()` and `end()`; renamed functions, added `push_front`, `push_back`, `write`, and `read`; added `insert()`; added move semantics; added iterator.

## Class `shs::ByteCollector`

### Description

`shs::ByteCollector` is a template class that provides functionality for managing a dynamic byte array. It supports various operations for adding, reading, and manipulating byte data.

### Template Parameters

`BCbuf_t` — type of the buffer used to store bytes. Default is `uint8_t`.

`BCsize_t`— type used for size representation. Default is `uint8_t`.

### Constructor

#### `explicit ByteCollector(BCsize_t size = 0)`

##### Parameters

- **size** — the initial size of the buffer. Default is `0`.

### Destructor

#### `~ByteCollector()`

- Cleans up the allocated memory for the byte buffer.

### Methods

#### Write Operations

- `void write(const BCbuf_t* begin, const BCsize_t size)`— writes a specified number of bytes from the provided buffer to the end of the buffer.

- `template <typename T> void push_back(const T& value, const BCsize_t bytes = sizeof(T))` — adds a value to the end of the buffer. The number of bytes to write can be specified.

- `template <typename T> void push_front(const T& value, const BCsize_t bytes = sizeof(T))` — adds a value to the beginning of the buffer. The number of bytes to write can be specified.

- `void insert(const BCbuf_t* ptr, const BCsize_t size, const BCsize_t position)` — inserts a specified number of bytes at a given position in the buffer.

- `template <typename T> void insert(const T& value, const BCsize_t size, const BCsize_t position)` — inserts a value at a specified position in the buffer.

#### Read Operations

- `void read(BCbuf_t* begin, const BCsize_t size)` — reads a specified number of bytes from the buffer into the provided buffer.

- `template <typename T> void get(T& var, const BCsize_t bytes = sizeof(T))` — retrieves a value from the buffer and stores it in the provided variable.

- `BCbuf_t& back() const` — returns a reference to the last byte in the byte collector.

#### Size Management

- `void reserve(const BCsize_t size)` — reserves additional space in the buffer.

- `void reserve_front(const BCsize_t size)` — reserves additional space at the front of the buffer.

- `BCsize_t capacity() const` — returns the total allocated size of the buffer.

- `BCsize_t capacity_front() const` — returns the amount of space available at the front of the buffer.

- `BCsize_t capacity_back() const` — returns the amount of space available at the back of the buffer.

- `BCsize_t size() const` — returns the number of bytes currently stored in the buffer.

- `void shrink_to_fit()` — reduces the capacity of the buffer to fit its current size.

- `void shrink_to_read()` — frees up memory from the portion of the buffer that has been read, reducing the size of the buffer to only include unread data.

#### Position Management

- `BCsize_t setPositionBack(const BCsize_t position)` — sets the current position at the back of the buffer.

- `BCsize_t setPositionFront(const BCsize_t position)` — sets the current position at the front of the buffer.

- `BCsize_t setPositionRead(const BCsize_t position)` — sets the current read position in the buffer.

- `BCsize_t getPositionBack() const` — returns the current position at the back of the buffer.

- `BCsize_t getPositionFront() const` — returns the current position at the front of the buffer.

- `BCsize_t getPositionRead() const` — returns the current read position in the buffer.

#### Utility Functions

- `bool empty() const` — checks if the buffer is empty.

- `BCbuf_t* getPtr() const` — returns a pointer to the underlying byte buffer.

- `shs::ByteCollectorIterator<BCbuf_t> begin() const` — returns an iterator to the beginning of the buffer.

- `shs::ByteCollectorIterator<BCbuf_t> end() const` — returns an iterator to the end of the buffer.

- `BCbuf_t& operator[](const BCsize_t index) const` — accesses the byte at the specified index in the buffer.

- `void reset()`— resets the positions in the buffer to zero.
- `void clear()` — clears the contents of the buffer and resets its positions.

- `BCsize_t readAvailable() const` — returns the number of bytes available for reading in the buffer.

- `shs::ByteCollectorReadIterator<BCbuf_t, BCsize_t> getReadIt(const bool set_begin = false) const`— returns a read iterator for the buffer, optionally setting the beginning position.

#### Operators

- `BCbuf_t& operator[](const BCsize_t index) const` — accesses the byte at the specified index in the buffer.

- `shs::ByteCollector<BCbuf_t, BCsize_t>& operator+=(const T& other)` — adds a value to the byte collector.

### Example Usage

```cpp
shs::ByteCollector<uint8_t, uint8_t> bc;
int value = 1000;

bc.push_back(value, 2);               // Adds 2 bytes of the integer value
bc.get(value, 2);
```

## Conclusion

The `shs::ByteCollector` class provides a flexible and efficient way to manage byte data in memory, making it suitable for various applications in data transfer protocols and other scenarios where byte manipulation is required.
