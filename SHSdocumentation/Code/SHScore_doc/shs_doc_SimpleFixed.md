# shs::SimpleFixed Class Documentation

## General Description

The `shs::SimpleFixed` class provides a flexible and efficient way to work with fixed-point numbers in the Smart Home System. This implementation allows for precise arithmetic operations while maintaining good performance, making it particularly useful in embedded systems and other environments where floating-point operations might be costly. The class is designed to ensure cross-platform compatibility when transmitting `float` and `double` variables.

## Versions

- **v2.0.0** — created.

---

## Class `shs::SimpleFixed`

### Description

`shs::SimpleFixed` implements fixed-point arithmetic, allowing for the representation of decimal values with a specified precision (power of ten). The internal representation uses a 64-bit integer, where the lower 4 bits store the power of ten (resolution), and the remaining 60 bits store the actual value. This design ensures that fixed-point numbers can be transmitted across different platforms without loss of precision.

### Constants

- **`DEFAULT_POWER_OF_TEN`**
  - Type: `static constexpr auto`
  - Value: `4`
  - Description: Default precision for fixed-point numbers (10^4).

### Members

- **`int64_t m_value`**
  - Description: Internal representation of the fixed-point number, combining the value and resolution.

---

### Constructors

- ##### `SimpleFixed(value, power_of_ten)`

  ```cpp
  SimpleFixed(const double value = 0, const uint8_t power_of_ten = DEFAULT_POWER_OF_TEN) noexcept;
  ```

  - ##### Description

    Initializes a `SimpleFixed` instance with a specified value and precision.

  - ##### Parameters

    - `value` — Initial value (default is 0).
    - `power_of_ten` — Precision as a power of ten (default is `DEFAULT_POWER_OF_TEN`).

---

### Methods

- ##### `void set(value, power_of_ten)`

  ```cpp
  void set(const int64_t value, const uint8_t power_of_ten = 0);
  void set(const float value, const uint8_t power_of_ten = 0);
  void set(const double value, const uint8_t power_of_ten = 0);
  ```

  - ##### Description

    Sets the value and optionally the precision of the fixed-point number.

  - ##### Parameters

    - `value` — The value to set.
    - `power_of_ten` — Optional new precision (default is 0, which keeps current precision).

---

- ##### `int64_t getRAW() const`

  ```cpp
  int64_t getRAW() const;
  ```

  - ##### Description

    Returns the raw internal representation of the fixed-point number.

---

- ##### `int64_t getRAWvalue() const`

  ```cpp
  int64_t getRAWvalue() const;
  ```

  - ##### Description

    Returns the raw value part of the fixed-point number (without considering the resolution).

---

- ##### `uint8_t getResolution() const`

  ```cpp
  uint8_t getResolution() const;
  ```

  - ##### Description

    Returns the current precision (power of ten) of the fixed-point number.

---

- ##### `void setResolution(power_of_ten)`

  ```cpp
  void setResolution(const uint8_t power_of_ten);
  ```

  - ##### Description

    Sets a new precision for the fixed-point number.

  - ##### Parameters

    - `power_of_ten` — New precision as a power of ten.

---

### Conversion Methods

- ##### `float toFloat() const`

  ```cpp
  float toFloat() const;
  ```

  - ##### Description

    Converts the fixed-point number to a floating-point value.

---

- ##### `double toDouble() const`

  ```cpp
  double toDouble() const;
  ```

  - ##### Description

    Converts the fixed-point number to a double-precision floating-point value.

---

- ##### `int64_t toInt() const`

  ```cpp
  int64_t toInt() const;
  ```

  - ##### Description

    Converts the fixed-point number to an integer value.

---

### Type Conversion Operators

The class provides implicit conversion operators to various numeric types:

- `operator float()`
- `operator double()`
- `operator int64_t()`
- `operator int32_t()`
- `operator int16_t()`
- `operator int8_t()`
- `operator uint64_t()`
- `operator uint32_t()`
- `operator uint16_t()`
- `operator uint8_t()`

### Assignment Operators

The class provides assignment operators for various numeric types:

- `operator=(const int64_t value)`
- `operator=(const int32_t value)`
- `operator=(const float value)`
- `operator=(const double value)`

---

### Example Usage

```cpp
// Create a fixed-point number with default precision (10^4)
shs::SimpleFixed fixed(12.3456);

// Get the value in different formats
double d = fixed.toDouble();    // 12.3456
float f = fixed.toFloat();      // 12.3456f
int i = fixed.toInt();          // 12

// Change the precision
fixed.setResolution(2);         // Now represents numbers with 2 decimal places
fixed.set(15.67);               // Set new value with new precision

// Use implicit conversions
float new_f = fixed;            // Automatically converts to float
```

---

## Conclusion

The `shs::SimpleFixed` class provides a flexible and efficient way to work with fixed-point numbers in the Smart Home System. Its implementation allows for precise arithmetic operations while maintaining good performance, making it particularly useful in embedded systems and other environments where floating-point operations might be costly. This class ensures cross-platform compatibility when transmitting `float` and `double` variables, facilitating seamless data exchange between different components of the system.
