# shs_DTPdiscover.h

## General Description

This file contains the definition of the `shs::DTPdiscover` class, which is a component of the Smart Home System Data Transfer Protocol (SHSDTP). The class is responsible for discovering devices on a local network, facilitating communication and integration within the system.

## Versions

- **v2.0.0** — created a new component of DTP.

---

## Class `shs::DTPdiscover`

### Inheritance

`shs::DTPdiscover` inherits from `shs::Process` and `shs::API`.

### Description

`shs::DTPdiscover` is a class designed to search for devices on a local network. It provides methods for initiating discovery, waiting for responses, and checking the status of devices. The class uses UDP broadcasting to communicate with devices and manage discovery requests.

### Members

- `shs::UdpBroadcastBus m_udp_broadcast` — UDP broadcast bus used for sending and receiving discovery messages.
- `shs::SortedBuf<shs::DTPdiscover::m_Data, shs::DTPdiscover::m_Data_less> m_requests` — Buffer containing discovery requests and their statuses.

---

### Constructor

- ##### `DTPdiscover(moduleID, udp_broadcast_port)`

  ```cpp
  DTPdiscover(shs::t::shs_ID_t moduleID, const shs::t::shs_port_t udp_broadcast_port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Initializes the DTPdiscover instance with a specified module ID and an optional UDP broadcast port.

---

### Methods

#### Discovery

- ##### `void discover(id)`

  ```cpp
  void discover(const uint8_t id);
  ```

  - ##### Description

    Initiates the discovery process for a device with the specified ID.

  - ##### Parameters

    - `id` — the ID of the device to discover.

---

- ##### `shs::t::shs_IP_t discoverWait(id, max_time)`

  ```cpp
  shs::t::shs_IP_t discoverWait(const uint8_t id, const uint16_t max_time);
  ```

  - ##### Description

    Initiates the discovery process and waits for a response within the specified maximum time.

  - ##### Parameters

    - `id` — the ID of the device to discover.
    - `max_time` — the maximum time to wait for a response.

  - ##### Returns

    The IP address of the discovered device, or 0 if not found.

---

- ##### `shs::t::shs_IP_t check(id)`

  ```cpp
  shs::t::shs_IP_t check(const uint8_t id);
  ```

  - ##### Description

    Checks the status of a discovery request for a device with the specified ID.

  - ##### Parameters

    - `id` — the ID of the device to check.

  - ##### Returns

    The IP address of the device if discovered, or 0 if not found.

---

#### Overloaded Methods

- ##### `void start()`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the UDP broadcast bus for discovery.

---

- ##### `void tick()`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Updates the state of the DTPdiscover instance and processes incoming discovery responses.

---

- ##### `void stop()`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the UDP broadcast bus.

---

### Example Usage

```cpp
shs::DTPdiscover discover(MODULE_ID);  // Create a DTPdiscover instance with a specific module ID
discover.start();                      // Start the discovery process
auto ip = discover.discover(SOME_ID);
```

---

## Conclusion

The `shs::DTPdiscover` class is an essential component of the Smart Home System, enabling the discovery of devices on a local network. Its methods facilitate the initiation and management of discovery requests, ensuring efficient communication and integration within the system.
