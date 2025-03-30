# shs_IP.h

## General Description

This file contains the definition of the `shs::IP` structure, which is used to represent an IP address within the Smart Home System. The structure provides methods for constructing IP addresses from strings or numeric values, as well as converting between different formats.

## Versions

- **v2.0.0** — created.

---

## Structure `shs::IP`

### Description

`shs::IP` is a structure that encapsulates an IP address, allowing for easy manipulation and conversion between different representations. It provides constructors for creating IP addresses from strings, numeric values, and other IP address types.

### Members

- `uint32_t m_IP` — The internal representation of the IP address as a 32-bit unsigned integer.

---

### Constructors

- ##### `IP(ipAddress)`

  ```cpp
  constexpr IP(const char* ipAddress);
  ```

  - ##### Description

    Initializes an IP instance from a string representation of an IP address.

  - ##### Parameters

    - `ipAddress` — The string representation of the IP address.

---

- ##### `IP(ipAddress)`

  ```cpp
  constexpr IP(const uint32_t ipAddress = 0);
  ```

  - ##### Description

    Initializes an IP instance from a numeric representation of an IP address.

  - ##### Parameters

    - `ipAddress` — The numeric representation of the IP address (default is 0).

---

- ##### `IP(ipAddress)`

  ```cpp
  IP(const IPAddress& ipAddress);
  ```

  - ##### Description

    Initializes an IP instance from an `IPAddress` object (specific to ESP platforms).

  - ##### Parameters

    - `ipAddress` — The `IPAddress` object to convert.

---

### Assignment Operators

- ##### `operator=(ipAddress)`

  ```cpp
  IP& operator=(const char* ipAddress);
  ```

  - ##### Description

    Assigns a new IP address from a string representation.

  - ##### Parameters

    - `ipAddress` — The string representation of the new IP address.

  - ##### Returns

    A reference to the current IP instance.

---

- ##### `operator=(ipAddress)`

  ```cpp
  IP& operator=(const uint32_t ipAddress);
  ```

  - ##### Description

    Assigns a new IP address from a numeric representation.

  - ##### Parameters

    - `ipAddress` — The numeric representation of the new IP address.

  - ##### Returns

    A reference to the current IP instance.

---

### Methods

- ##### `static uint32_t ipFromStr(ip)`

  ```cpp
  static constexpr uint32_t ipFromStr(const char* ip);
  ```

  - ##### Description

    Converts a string representation of an IP address to a numeric format.

  - ##### Parameters

    - `ip` — The string representation of the IP address.

  - ##### Returns

    The numeric representation of the IP address.

---

- ##### `operator uint32_t()`

  ```cpp
  operator uint32_t() const;
  ```

  - ##### Description

    Converts the IP address to its numeric representation.

  - ##### Returns

    The numeric representation of the IP address.

---

- ##### `operator IPAddress()`

  ```cpp
  operator IPAddress() const;
  ```

  - ##### Description

    Converts the IP address to an `IPAddress` object (specific to ESP platforms).

  - ##### Returns

    The `IPAddress` representation of the IP address.

---

### Static Functions

- ##### `static uint32_t reverse_bytes(ip)`

  ```cpp
  static constexpr uint32_t reverse_bytes(const uint32_t ip);
  ```

  - ##### Description

    Reverses the byte order of the given IP address.

  - ##### Parameters

    - `ip` — The numeric representation of the IP address.

  - ##### Returns

    The IP address with reversed byte order.

---

### Example Usage

```cpp
shs::IP myIP("192.168.1.1"); // Create an IP instance from a string
uint32_t numericIP = myIP;   // Convert to numeric representation
```

---

## Conclusion

The `shs::IP` structure is a crucial component of the Smart Home System, providing a robust mechanism for representing and manipulating IP addresses. Its methods and operators facilitate easy conversion and management of IP addresses, ensuring efficient communication within the system.