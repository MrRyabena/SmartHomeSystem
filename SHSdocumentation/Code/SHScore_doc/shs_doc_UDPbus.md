# shs_UDPbus.h

## General Description

This file contains the definitions of the `shs::UdpBus`, `shs::UdpBroadcastBus`, and `shs::UdpMulticastBus` classes, which provide functionality for managing UDP communication in the Smart Home System. These classes extend the `shs::DTPbus` class to facilitate unicast, broadcast, and multicast communication.

## Versions

- **v2.0.0** — created.

---

## Class `shs::UdpBus`

### Description

`shs::UdpBus` is a class that manages unicast UDP communication. It allows sending and receiving DTP packets over a specified IP address and port. The class inherits from `shs::DTPbus`, enabling it to integrate with the DTP protocol for data transfer.

### Members

- **`shs::t::shs_IP_t m_ip`** — The IP address for the UDP communication.
- **`shs::t::shs_port_t m_port`** — The port number for the UDP communication.
- **`shs::UDP m_udp`** — The underlying UDP instance used for communication.

### Constructors

- ##### `UdpBus(ip, port, busID, handler, bufsize)`

  ```cpp
  explicit UdpBus(const shs::t::shs_IP_t ip, const shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25);
  ```

  - ##### Description

    Initializes a `UdpBus` instance with the specified IP address, port, bus ID, and optional API handler.

  - ##### Parameters

    - `ip` — The IP address for the UDP communication.
    - `port` — The port number for the UDP communication.
    - `busID` — The bus ID for the DTP communication.
    - `handler` — Optional API handler for processing incoming messages.
    - `bufsize` — Size of the buffer for DTP communication (default is 25).

---

### Methods

- ##### `shs::DTPbus::Status checkBus() override`

  ```cpp
  shs::DTPbus::Status checkBus() override;
  ```

  - ##### Description

    Checks the status of the UDP bus.

---

- ##### `uint8_t sendPacket(const shs::DTPpacket& packet) override`

  ```cpp
  uint8_t sendPacket(const shs::DTPpacket& packet) override;
  ```

  - ##### Description

    Sends a DTP packet over the UDP bus.

  - ##### Parameters

    - `packet` — The DTP packet to send.

  - ##### Returns

    The result of the send operation.

---

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the UDP bus and begins listening for incoming packets.

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Processes incoming packets on the UDP bus.

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the UDP bus and disconnects from any active connections.

---

## Class `shs::UdpBroadcastBus`

### Description

`shs::UdpBroadcastBus` is a class that manages broadcast UDP communication. It allows sending DTP packets to all devices on the local network. The class inherits from `shs::DTPbus`, enabling it to integrate with the DTP protocol for data transfer.

### Members

- **`shs::t::shs_port_t m_port`** — The port number for the broadcast communication.
- **`shs::UDP m_udp`** — The underlying UDP instance used for communication.

### Constructors

- ##### `UdpBroadcastBus(port, busID, handler, bufsize)`

  ```cpp
  explicit UdpBroadcastBus(const shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25);
  ```

  - ##### Description

    Initializes a `UdpBroadcastBus` instance with the specified port, bus ID, and optional API handler.

  - ##### Parameters

    - `port` — The port number for the broadcast communication.
    - `busID` — The bus ID for the DTP communication.
    - `handler` — Optional API handler for processing incoming messages.
    - `bufsize` — Size of the buffer for DTP communication (default is 25).

---

### Methods

- ##### `bool isActive() const override`

  ```cpp
  bool isActive() const override;
  ```

  - ##### Description

    Checks if the broadcast bus is active.

  - ##### Returns

    `true` if the bus is active; otherwise, `false`.

---

- ##### `shs::DTPbus::Status checkBus() override`

  ```cpp
  shs::DTPbus::Status checkBus() override;
  ```

  - ##### Description

    Checks the status of the broadcast bus.

---

- ##### `uint8_t sendPacket(const shs::DTPpacket& packet) override`

  ```cpp
  uint8_t sendPacket(const shs::DTPpacket& packet) override;
  ```

  - ##### Description

    Sends a DTP packet as a broadcast.

  - ##### Parameters

    - `packet` — The DTP packet to send.

  - ##### Returns

    The result of the send operation.

---

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the broadcast bus and begins listening for incoming packets.

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Processes incoming packets on the broadcast bus.

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the broadcast bus and disconnects from any active connections.

---

## Class `shs::UdpMulticastBus`

### Description

`shs::UdpMulticastBus` is a class that manages multicast UDP communication. It allows sending DTP packets to a group of devices on the network. The class inherits from `shs::DTPbus`, enabling it to integrate with the DTP protocol for data transfer.

### Members

- **`shs::t::shs_IP_t m_multicastIP`** — The multicast IP address for the communication.
- **`shs::t::shs_port_t m_port`** — The port number for the multicast communication.
- **`shs::UDP m_udp`** — The underlying UDP instance used for communication.

### Constructors

- ##### `UdpMulticastBus(multicastIP, port, busID, handler, bufsize)`

  ```cpp
  explicit UdpMulticastBus(const shs::t::shs_IP_t multicastIP, shs::t::shs_port_t port, const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25);
  ```

  - ##### Description

    Initializes a `UdpMulticastBus` instance with the specified multicast IP, port, bus ID, and optional API handler.

  - ##### Parameters

    - `multicastIP` — The multicast IP address for the communication.
    - `port` — The port number for the multicast communication.
    - `busID` — The bus ID for the DTP communication.
    - `handler` — Optional API handler for processing incoming messages.
    - `bufsize` — Size of the buffer for DTP communication (default is 25).

---

### Methods

- ##### `shs::DTPbus::Status checkBus() override`

  ```cpp
  shs::DTPbus::Status checkBus() override;
  ```

  - ##### Description

    Checks the status of the multicast bus.

---

- ##### `uint8_t sendPacket(const shs::DTPpacket& packet) override`

  ```cpp
  uint8_t sendPacket(const shs::DTPpacket& packet) override;
  ```

  - ##### Description

    Sends a DTP packet as a multicast.

  - ##### Parameters

    - `packet` — The DTP packet to send.

  - ##### Returns

    The result of the send operation.

---

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the multicast bus and begins listening for incoming packets.

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Processes incoming packets on the multicast bus.

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the multicast bus and disconnects from any active connections.

---

## Conclusion

The `shs::UdpBus`, `shs::UdpBroadcastBus`, and `shs::UdpMulticastBus` classes provide comprehensive interfaces for managing UDP communication within the Smart Home System. By supporting unicast, broadcast, and multicast communication, they facilitate efficient data transmission between devices in the network.
