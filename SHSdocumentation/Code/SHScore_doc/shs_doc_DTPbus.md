# shs_DTPbus.h

## General Description

This file contains the definition of the `shs::DTPbus` class, which serves as an **abstract** class for a data bus that accepts and sends messages within the _Smart Home System Data Transfer Protocol_ (SHSDTP). The class provides a framework for implementing various types of data buses, enabling efficient communication between components.

## Versions

- **v0.1.0** — created.
- **v0.2.0** — divided into two classes, introduced new types of handlers, added inheritance from `shs::CallbacksKeeper`, and utilized a new class for CRC.
- **v1.0.0** — release; added namespaces and corrected variable names.
- **v2.0.0** — global changes, divided into components and expanded functionality:
  - Introduced component classes:
    - `shs::DTP` — container class for linking data buses and API handlers.
    - `shs::DTPbus` — abstract class for a data bus that accepts and sends messages.
    - `shs::DTPdiscover` — class for searching for devices on a local network.
    - `shs::DTPless` — comparison operators for search and sorting algorithms.
    - `shs::DTPpacket` — class for creating, encrypting, and decrypting messages.
  - Conducted extensive testing.

---

## Class `shs::DTPbus`

### Inheritance

`shs::DTPbus` inherits from `shs::Process`.

### Description

`shs::DTPbus` is an abstract class that defines the interface for data buses in the Smart Home System. It provides methods for sending and processing messages, managing connected modules, and handling the lifecycle of the bus.

### Members

- `shs::t::shs_busID_t busID` — identifier for the bus associated with this DTPbus instance.
- `Status status` — current status of the bus.
- `shs::SortedBuf<uint8_t> connected_modules` — buffer containing IDs of connected modules.

---

### Constructor

- ##### `DTPbus(busID, handler, bufsize)`

  ```cpp
  explicit DTPbus(const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25);
  ```

  - ##### Description

    Initializes the DTPbus instance with a specified bus ID and an optional API handler.

---

### Destructor

- ##### `~DTPbus()`

  ```cpp
  virtual ~DTPbus() = default;
  ```

  - ##### Description

    Cleans up resources used by the DTPbus instance.

---

### Methods

#### Bus Management

- ##### `Status checkBus()`

  ```cpp
  virtual Status checkBus() = 0;
  ```

  - ##### Description

    Checks the status of the bus and processes incoming data.

  - ##### Returns

    The current status of the bus.

---

- ##### `uint8_t sendPacket(packet)`

  ```cpp
  virtual uint8_t sendPacket(const shs::DTPpacket& packet) = 0;
  ```

  - ##### Description

    Sends a DTP packet to the appropriate data bus based on the recipient ID.

  - ##### Parameters

    - `packet` — the DTP packet to send.

---

- ##### `uint8_t sendRAW(data, id)`

  ```cpp
  virtual uint8_t sendRAW(shs::ByteCollector<>& bc, const uint8_t id) = 0;
  ```

  - ##### Description

    Sends raw byte data to the specified module ID.

  - ##### Parameters

    - `bc` — the byte collector containing the data to send.
    - `id` — the module ID to send the data to.

---

#### Overloaded Methods

- ##### `void start()`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Initiates the data bus.

---

- ##### `void tick()`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Updates the state of the DTPbus instance and processes incoming data.

---

- ##### `void stop()`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the data bus.

---

## Conclusion

The `shs::DTPbus` class is a fundamental component of the Smart Home System, providing a flexible and extensible framework for managing data buses. Its methods facilitate the sending and receiving of data packets, as well as the management of connected modules, ensuring robust communication within the system.