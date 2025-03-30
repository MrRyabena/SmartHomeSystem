# shs_Load

## General Description

This file contains the definitions and includes for various load-related components within the Smart Home System. It serves as a central point for managing different types of load functionalities, including load switches and virtual loads.

## Versions

- **v2.0.0** — created.

---

## Included Components

This file includes the following components:

- `shs_Load.h` — Main header file for load management.
- `shs_Load_API.h` — API definitions for interacting with load components.
- `shs_LoadSwitch.h` — Definitions for load switch components.
- `shs_LoadSwitchReversed.h` — Definitions for reversed load switch components.
- `shs_LoadVirtual.h` — Definitions for virtual load components.

---

# shs_Load.h

## General Description

This file contains the definition of the `shs::Load` class, which serves as an abstract representation of a load (electrical device or component) within the Smart Home System. The class provides a framework for different types of loads, allowing for consistent interaction and control.

## Versions

- **v0.1.0** — created.
- **v0.2.0** — corrected.
- **v1.0.0** — release; namespaces added and variable names corrected.
- **v2.0.0** — redesigned, debugged, and tested.

---

## Class `shs::Load`

### Description

`shs::Load` is an abstract class that describes a load (electrical device or component) within the Smart Home System. It provides a common interface for various types of loads, enabling efficient control and management of electrical components.

### Members

- `enum Type` — Defines the different types of loads:
  - `UNKNOWN` — Represents an unknown load type.
  - `SWITCH` — Represents a standard switch.
  - `SWITCH_REVERSED` — Represents a reversed switch.
  - `PID` — Represents a PID-controlled load.
  - `PWM` — Represents a PWM-controlled load.
  - `DIMMER` — Represents a dimmer load.
  - `USER_TYPES` — Represents user-defined load types.

- `uint16_t m_value` — The current value of the load.

---

### Constructor

- ##### `Load(l_type)`

  ```cpp
  explicit Load(const Type l_type = UNKNOWN);
  ```

  - ##### Description

    Initializes a Load instance with a specified load type.

  - ##### Parameters

    - `l_type` — The type of the load (default is `UNKNOWN`).

---

### Destructor

- ##### `~Load()`

  ```cpp
  virtual ~Load() = default;
  ```

  - ##### Description

    Cleans up resources used by the Load instance.

---

### Methods

- ##### `void setup()`

  ```cpp
  virtual void setup() = 0;
  ```

  - ##### Description

    Sets up the load. This method must be implemented by derived classes.

---

- ##### `void on(value)`

  ```cpp
  virtual void on(const uint16_t value = UINT16_MAX) = 0;
  ```

  - ##### Description

    Turns the load on with an optional value.

  - ##### Parameters

    - `value` — The value to set when turning on the load (default is `UINT16_MAX`).

---

- ##### `void off()`

  ```cpp
  virtual void off() = 0;
  ```

  - ##### Description

    Turns the load off. This method must be implemented by derived classes.

---

- ##### `uint16_t getValue() const`

  ```cpp
  [[nodiscard]] uint16_t getValue() const noexcept;
  ```

  - ##### Description

    Retrieves the current value of the load.

  - ##### Returns

    The current value of the load as a `uint16_t`.

---

### Example Usage

```cpp
shs::Load myLoad(shs::Load::SWITCH);  // Create a Load instance with type SWITCH
myLoad.setup();   // Set up the load
myLoad.on(100);   // Turn on the load
myLoad.off();     // Turn off the load
```

---

## Conclusion

The `shs::Load` class is a fundamental component of the Smart Home System, providing a robust mechanism for representing and managing electrical loads. Its methods and constructors facilitate easy manipulation and control of various load types, ensuring efficient operation within the system.
