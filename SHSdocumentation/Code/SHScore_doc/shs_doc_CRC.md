# shs_CRC.h

## General Description

This file contains the definition of the `shs::CRC8`, `shs::CRC16`, and `shs::CRC32` classes, which provide functionality for calculating CRC (Cyclic Redundancy Check) values. These classes are essential for ensuring data integrity in communication protocols and data storage.

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v1.1.0** — updated methods to write results to a variable.
- **v1.2.0** — optimized CRC calculations.
- **v2.0.0** — added static methods in `shs::CRC8` and fixed bugs.

---

## Class `shs::CRC8`

### Description

`shs::CRC8` is a class that implements the CRC-8 algorithm for error-checking in data transmission.

### Members

- `uint8_t crc` — the current CRC value.
- `static constexpr uint8_t CRC8_poly = 0x00` — the initial polynomial value used in the CRC algorithm.

### Methods

- ##### `void add(value)`

  ```cpp
  void add(const uint8_t value);
  ```

  - ##### Description

    Adds a value to the current CRC calculation.

  - ##### Parameters

    - `value` — the value to add to the CRC calculation.

- ##### `void clear()`

  ```cpp
  void clear();
  ```

  - ##### Description

    Resets the CRC value to the initial state.

- ##### `uint8_t addBuf(ptr, size)`

  ```cpp
  uint8_t addBuf(const uint8_t* ptr, uint16_t size);
  ```

  - ##### Description

    Adds a buffer of data to the CRC calculation and returns the final CRC value.

  - ##### Parameters

    - `ptr` — pointer to the buffer of data.
    - `size` — the number of bytes in the buffer.

---

#### Static Methods

- ##### `void update(crc, data)`

  ```cpp
  static void update(uint8_t& crc, const uint8_t data);
  ```

  - ##### Description

    Updates the CRC value based on the input data byte.

  - ##### Parameters

    - `crc` — reference to the current CRC value.
    - `data` — the data byte to update the CRC with.

- ##### `uint8_t crcBuf(ptr, size)`

  ```cpp
  static uint8_t crcBuf(const uint8_t* ptr, uint16_t size);
  ```

  - ##### Description

    Calculates the CRC value for a given buffer of data.

  - ##### Parameters

    - `ptr` — pointer to the buffer of data.
    - `size` — the number of bytes in the buffer.

---

## Class `shs::CRC16`

### Description

`shs::CRC16` is a class that implements the CRC-16 algorithm for error-checking in data transmission.

### Members

- `uint16_t crc` — the current CRC value.
- `static constexpr uint16_t CRC16_poly = 0xFFFF` — the initial polynomial value used in the CRC algorithm.

### Methods

- ##### `void add(value)`

  ```cpp
  void add(const uint8_t value);
  ```

  - ##### Description

    Adds a value to the current CRC calculation.

  - ##### Parameters

    - `value` — the value to add to the CRC calculation.

- ##### `void clear()`

  ```cpp
  void clear();
  ```

  - ##### Description

    Resets the CRC value to the initial state.

---

#### Static Methods

- ##### `void update(crc, data)`

  ```cpp
  static void update(uint16_t& crc, uint8_t data);
  ```

  - ##### Description

    Updates the CRC value based on the input data byte.

  - ##### Parameters

    - `crc` — reference to the current CRC value.
    - `data` — the data byte to update the CRC with.

- ##### `uint16_t crcBuf(ptr, size)`

  ```cpp
  static uint16_t crcBuf(const uint8_t* ptr, uint16_t size);
  ```

  - ##### Description

    Calculates the CRC value for a given buffer of data.

  - ##### Parameters

    - `ptr` — pointer to the buffer of data.
    - `size` — the number of bytes in the buffer.

---

## Class `shs::CRC32`

### Description

`shs::CRC32` is a class that implements the CRC-32 algorithm for error-checking in data transmission.

### Members

- `uint32_t crc` — the current CRC value.
- `static constexpr uint32_t CRC32_poly = 0xFFFFFFFF` — the initial polynomial value used in the CRC algorithm.

### Methods

- ##### `void add(value)`

  ```cpp
  void add(const uint8_t value);
  ```

  - ##### Description

    Adds a value to the current CRC calculation.

  - ##### Parameters

    - `value` — the value to add to the CRC calculation.

- ##### `void clear()`

  ```cpp
  void clear();
  ```

  - ##### Description

    Resets the CRC value to the initial state.

---

#### Static Methods

- ##### `void update(crc, data)`

  ```cpp
  static void update(uint32_t& crc, uint8_t data);
  ```

  - ##### Description

    Updates the CRC value based on the input data byte.

  - ##### Parameters

    - `crc` — reference to the current CRC value.
    - `data` — the data byte to update the CRC with.

- ##### `uint32_t crcBuf(ptr, size)`

  ```cpp
  static uint32_t crcBuf(const uint8_t* ptr, uint16_t size);
  ```

  - ##### Description

    Calculates the CRC value for a given buffer of data.

  - ##### Parameters

    - `ptr` — pointer to the buffer of data.
    - `size` — the number of bytes in the buffer.

---

### Example Usage

```cpp
#include <cassert>
#include <shs_CRC.h>

int main()
{
    constexpr uint8_t data[]{0x01, 0x02, 0x03};
    shs::CRC8 crc8;

    crc8.addBuf(data, std::size(data));

    uint8_t crc8_manual = shs::CRC8::CRC8_poly;
    for (auto i = 0; i < std::size(data); i++) 
        shs::CRC8::update(crc8_manual, data[i]);

    auto crc8_value = shs::CRC8::crcBuf(data, std::size(data));

    assert(crc8.crc == crc8_manual);
    assert(crc8.crc == crc8_value);
}
```

---

## Conclusion

The `shs::CRC8`, `shs::CRC16`, and `shs::CRC32` classes provide efficient implementations of CRC algorithms, ensuring data integrity in various applications. These classes are essential for developers working with communication protocols and data storage systems.
