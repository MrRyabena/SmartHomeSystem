# shs_LoadVirtual.h

## General Description

This file contains the definition of the `shs::LoadVirtual` class, which represents a virtual load in the Smart Home System. The class provides an interface for controlling virtual loads and interacting with the associated API.

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — redesigned, debugged, and tested.

---

## Class `shs::LoadVirtual`

### Description

`shs::LoadVirtual` is a class that implements a virtual load, allowing for control and interaction with load devices that may not be physically present. It provides methods for setting up the load, turning it on and off, and handling API requests.

### Members

- `shs::t::shs_ID_t m_virtualID` — The ID of the virtual load.
- `shs::DTP& m_dtp` — Reference to the DTP instance used for communication.

---

### Constructor

- ##### `LoadVirtual(thisID, virtualID, dtp, l_type)`

  ```cpp
  LoadVirtual(const shs::t::shs_ID_t thisID, shs::t::shs_ID_t virtualID, shs::DTP& dtp, const Type l_type = shs::Load::Type::UNKNOWN);
  ```

  - ##### Description

    Initializes a LoadVirtual instance with specified IDs and a DTP instance.

  - ##### Parameters

    - `thisID` — The ID of this virtual load.
    - `virtualID` — The ID of the virtual load.
    - `dtp` — Reference to the DTP instance for communication.
    - `l_type` — The type of the load (default is `UNKNOWN`).

---

### Methods

- ##### `void setup()`

  ```cpp
  void setup() override;
  ```

  - ##### Description

    Sets up the virtual load. This method must be implemented by derived classes.

---

- ##### `void on(value)`

  ```cpp
  void on(const uint16_t value = UINT16_MAX) override;
  ```

  - ##### Description

    Turns the virtual load on with an optional value.

  - ##### Parameters

    - `value` — The value to set when turning on the load (default is `UINT16_MAX`).

---

- ##### `void off()`

  ```cpp
  void off() override;
  ```

  - ##### Description

    Turns the virtual load off. This method must be implemented by derived classes.

---

## Conclusion

The `shs::LoadVirtual` class is a crucial component of the Smart Home System, providing a flexible mechanism for managing virtual loads. Its methods and constructors facilitate easy manipulation and control of virtual load types, ensuring efficient operation within the system.
