# shs_types.h

## General Description

This file contains type definitions used throughout the Smart Home System. These types provide a consistent way to handle various data representations, ensuring compatibility across different components of the system.

## Versions

- **v1.2.0** — created.
- **v2.0.0** — developed from `shs_settings_private.h`.

---

## Type Definitions

### Floating-Point Types

- **`shs_double_t`**
  - Type: `double` or `float`
  - Description: Represents a double-precision floating-point number. The actual type used depends on the `USE_FLOAT_FOR_DOUBLE` preprocessor directive.

### String Types

- **`shs_string_t`**
  - Type: `String` (for Arduino) or `std::string` (for other platforms)
  - Description: Represents a string type used for text handling. The actual type used depends on the platform (Arduino or standard C++).

### IP Address Type

- **`shs_IP_t`**
  - Type: `shs::IP`
  - Description: Represents an IP address using the `shs::IP` class.

### Floating-Point Fixed-Point Type

- **`shs_fixed_t`**
  - Type: `shs::SimpleFixed`
  - Description: Represents a fixed-point number using the `shs::SimpleFixed` class, allowing for precise arithmetic without floating-point errors.

### ID Types

- **`shs_ID_t`**
  - Type: `shs::ID`
  - Description: Represents a unique identifier using the `shs::ID` class.

- **`shs_moduleID_t`**
  - Type: `shs::ID::moduleID_t`
  - Description: Represents a module identifier, derived from the `shs::ID` class.

- **`shs_deviceID_t`**
  - Type: `shs::ID::deviceID_t`
  - Description: Represents a device identifier, derived from the `shs::ID` class.

- **`shs_componentID_t`**
  - Type: `shs::ID::componentID_t`
  - Description: Represents a component identifier, derived from the `shs::ID` class.

### Bus ID Type

- **`shs_busID_t`**
  - Type: `uint16_t`
  - Description: Represents a bus identifier, used for communication between components.

### Port Type

- **`shs_port_t`**
  - Type: `uint16_t`
  - Description: Represents a port number for network communication.

### Time Type

- **`shs_time_t`**
  - Type: `uint32_t`
  - Description: Represents time in milliseconds, used for timing operations and delays.

---

## Conclusion

The type definitions in `shs_types.h` provide a consistent and clear way to handle various data types across the Smart Home System. By using these types, developers can ensure compatibility and maintainability throughout the codebase.