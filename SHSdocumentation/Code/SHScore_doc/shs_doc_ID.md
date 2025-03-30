# shs_ID.h

## General Description

This file contains the definition of the `shs::ID` structure, which is used to represent a unique identifier for modules, devices, and components within the Smart Home System. The structure provides methods for constructing, manipulating, and comparing IDs, ensuring efficient identification and communication between components.

## Versions

- **v1.2.0** — created.
- **v2.0.0** — added comparison operators.

---

## Structure `shs::ID`

### Description

`shs::ID` is a structure that encapsulates a unique identifier composed of a module ID, device ID, and component ID. It provides methods for constructing IDs from individual components, retrieving component values, and performing comparisons.

### Members

- `uint32_t id` — The unique identifier composed of module, device, and component IDs.

### Type Aliases

- `using ID_t = uint32_t` — Type alias for the ID type.
- `using moduleID_t = uint8_t` — Type alias for the module ID type.
- `using deviceID_t = uint8_t` — Type alias for the device ID type.
- `using componentID_t = uint16_t` — Type alias for the component ID type.

---

### Constructors

- ##### `ID(module_id, device_id, component_id)`

  ```cpp
  constexpr ID(const moduleID_t module_id = 0, const deviceID_t device_id = 0, const componentID_t component_id = 0);
  ```

  - ##### Description

    Initializes an ID instance with specified module, device, and component IDs.

  - ##### Parameters

    - `module_id` — The module ID (default is 0).
    - `device_id` — The device ID (default is 0).
    - `component_id` — The component ID (default is 0).

---

### Methods

- ##### `moduleID_t getModuleID() const`

  ```cpp
  constexpr moduleID_t getModuleID() const;
  ```

  - ##### Description

    Retrieves the module ID from the unique identifier.

  - ##### Returns

    The module ID.

---

- ##### `deviceID_t getDeviceID() const`

  ```cpp
  constexpr deviceID_t getDeviceID() const;
  ```

  - ##### Description

    Retrieves the device ID from the unique identifier.

  - ##### Returns

    The device ID.

---

- ##### `componentID_t getComponentID() const`

  ```cpp
  constexpr componentID_t getComponentID() const;
  ```

  - ##### Description

    Retrieves the component ID from the unique identifier.

  - ##### Returns

    The component ID.

---

- ##### `ID& setModuleID(module)`

  ```cpp
  shs::ID& setModuleID(const moduleID_t module);
  ```

  - ##### Description

    Sets the module ID in the unique identifier.

  - ##### Parameters

    - `module` — The new module ID.

  - ##### Returns

    A reference to the current ID instance.

---

- ##### `ID& setDeviceID(device)`

  ```cpp
  shs::ID& setDeviceID(const deviceID_t device);
  ```

  - ##### Description

    Sets the device ID in the unique identifier.

  - ##### Parameters

    - `device` — The new device ID.

  - ##### Returns

    A reference to the current ID instance.

---

- ##### `ID& setComponentID(api)`

  ```cpp
  shs::ID& setComponentID(const componentID_t api);
  ```

  - ##### Description

    Sets the component ID in the unique identifier.

  - ##### Parameters

    - `api` — The new component ID.

  - ##### Returns

    A reference to the current ID instance.

---

### Overloaded Operators

- ##### `operator<`

  ```cpp
  bool operator<(const shs::ID& other) const;
  ```

  - ##### Description

    Compares this ID with another ID for less-than.

  - ##### Returns

    `true` if this ID is less than the other ID, `false` otherwise.

---

- ##### `operator>`

  ```cpp
  bool operator>(const shs::ID& other) const;
  ```

  - ##### Description

    Compares this ID with another ID for greater-than.

  - ##### Returns

    `true` if this ID is greater than the other ID, `false` otherwise.

---

- ##### `operator==`

  ```cpp
  bool operator==(const shs::ID& other) const;
  ```

  - ##### Description

    Compares this ID with another ID for equality.

  - ##### Returns

    `true` if both IDs are equal, `false` otherwise.

---

- ##### `operator!=`

  ```cpp
  bool operator!=(const shs::ID& other) const;
  ```

  - ##### Description

    Compares this ID with another ID for inequality.

  - ##### Returns

    `true` if both IDs are not equal, `false` otherwise.

---

### Example Usage

```cpp
constexpr shs::ID id(1, 2, 3);                     // Create an ID with module ID 1, device ID 2, and component ID 3
constexpr auto moduleID = deviceID.getModuleID();  // Retrieve the module ID
static_assert(moduleID == 2);
```

---

## Conclusion

The `shs::ID` structure is a crucial component of the Smart Home System, providing a robust mechanism for uniquely identifying modules, devices, and components. Its methods and operators facilitate easy manipulation and comparison of IDs, ensuring efficient communication within the system.
