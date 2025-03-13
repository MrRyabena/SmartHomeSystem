# shs_DTP.h

## General Description

This file contains the definition of the `shs::DTP` class, which serves as a container for linking data buses and API handlers in the Smart Home System Data Transfer Protocol (DTP). The class facilitates communication between different components of the system, allowing for efficient data transfer and processing.

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

## Class `shs::DTP`

### Inheritance

`shs::DTP` inherits from `shs::Process`.

### Description

`shs::DTP` is a class that manages the interaction between data buses and API handlers, enabling seamless communication within the Smart Home System. It provides methods for sending packets, attaching and detaching buses and APIs, and managing the lifecycle of these components.

### Members

- `shs::t::shs_ID_t moduleID` — Identifier for the module associated with this DTP instance.

---

### Constructor

- ##### `DTP(module_id)`

  ```cpp
  explicit DTP(const shs::t::shs_ID_t module_id);
  ```

  - ##### Description

    Initializes the DTP instance with a specified module ID.

---

### Destructor

- ##### `~DTP()`

  ```cpp
  ~DTP() override = default;
  ```

  - ##### Description

    Cleans up resources used by the DTP instance.

---

### Methods

#### Sending Data

- ##### `uint8_t sendRAW(data, id)`

  ```cpp
  uint8_t sendRAW(shs::ByteCollector<>& bc, const uint8_t id);                 // (1)
  uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it, const uint8_t id);     // (2)
  uint8_t sendRAW(const uint8_t* data, const uint8_t size, const uint8_t id);  // (3)
  ```

  - ##### Description

    (1) Sends raw byte data to the specified module ID.  
    (2) Sends raw byte data from a read iterator to the specified module ID.  
    (3) Sends raw byte data of a specified size to the specified module ID.  

  - ##### Parameters

    - `bc` — the byte collector containing the data to send.
    - `it` — the read iterator containing the data to send.
    - `data` — pointer to the data to send.
    - `size` — the size of the data to send.
    - `id` — the module ID to send the data to.

---

- ##### `uint8_t sendPacket(packet)`

  ```cpp
  uint8_t sendPacket(const shs::DTPpacket& packet);
  ```

  - ##### Description

    Sends a DTP packet to the appropriate data bus based on the recipient ID.

  - ##### Parameters

    - `packet` — the DTP packet to send.

---

#### Bus Management

- ##### `DTPbus* findBusFromModule(moduleID)`

  ```cpp
  shs::DTPbus* findBusFromModule(const uint8_t moduleID) const;
  ```

  - ##### Description

    Locates the data bus associated with the given module ID.

  - ##### Parameters

    - `moduleID` — the ID of the module to find the bus for.

---

- ##### `busID attachBus(bus)`

  ```cpp
  shs::t::shs_busID_t attachBus(std::unique_ptr<shs::DTPbus>&& bus);
  ```

  - ##### Description

    Attaches a new data bus to the DTP instance and returns its unique bus ID.

  - ##### Parameters

    - `bus` — the data bus to attach.

---

- ##### `void detachBus(id)`

  ```cpp
  void detachBus(const shs::t::shs_busID_t& id);
  ```

  - ##### Description

    Detaches the data bus associated with the given bus ID.

  - ##### Parameters

    - `id` — the bus ID to detach.

---

- ##### `DTPbus* getBus(id)`

  ```cpp
  shs::DTPbus* getBus(const shs::t::shs_busID_t& id) const;
  ```

  - ##### Description

    Retrieves the data bus associated with the given bus ID.

  - ##### Parameters

    - `id` — the bus ID to retrieve.

---

#### API Management

- ##### `void attachAPI(api)`

  ```cpp
  void attachAPI(std::unique_ptr<shs::API>&& api);
  ```

  - ##### Description

    Attaches a new API handler to the DTP instance.

  - ##### Parameters

    - `api` — the API handler to attach.

---

- ##### `void attachAPI(api)`

  ```cpp
  void attachAPI(shs::API* api);
  ```

  - ##### Description

    Attaches an external API handler to the DTP instance.

  - ##### Parameters

    - `api` — the external API handler to attach.

---

- ##### `void detachAPI(id)`

  ```cpp
  void detachAPI(const shs::t::shs_ID_t& id);
  ```

  - ##### Description

    Detaches the API handler associated with the given ID.

  - ##### Parameters

    - `id` — the ID of the API handler to detach.

---

- ##### `API& getAPI(id)`

  ```cpp
  shs::API& getAPI(const shs::t::shs_ID_t& id) const;
  ```

  - ##### Description

    Retrieves the API handler associated with the given ID.

  - ##### Parameters

    - `id` — the ID of the API handler to retrieve.

---

#### Overloaded Methods

- ##### `void start()`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Initiates all attached data buses.


- ##### `void tick()`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Updates the state of the DTP instance and processes incoming data.


- ##### `void stop()`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops all attached data buses.

---

### Private Members

- ##### `m_buss`

  ```cpp
  shs::SortedBuf<std::unique_ptr<shs::DTPbus>, DTPless::BUS> m_buss;
  ```

  - ##### Description

    A sorted buffer containing attached data buses.

- ##### `m_APIs`

  ```cpp
  shs::SortedBuf<std::unique_ptr<shs::API>, DTPless::API> m_APIs;
  ```

  - ##### Description

    A sorted buffer containing attached API handlers.

- ##### `m_externalAPIs`

  ```cpp
  shs::SortedBuf<shs::API*, DTPless::API> m_externalAPIs;
  ```

  - ##### Description

    A sorted buffer containing external API handlers.

---

### Example Usage

```cpp
shs::DTP dtpInstance(moduleID); // Create a DTP instance with a specific module ID
dtpInstance.start(); // Start the DTP process
```

---

## Conclusion

The `shs::DTP` class is a crucial component of the Smart Home System, enabling efficient communication between data buses and API handlers. Its methods facilitate the sending and receiving of data packets, as well as the management of connected components, ensuring a robust and flexible architecture for the system.