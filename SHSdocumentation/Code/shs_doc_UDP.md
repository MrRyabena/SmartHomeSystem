# shs_UDP.h

## General Description

This file contains the definition of the `shs::UDP` class, which provides functionality for sending and receiving UDP packets within the Smart Home System. The class is designed to work with different platforms, including Arduino and Qt, and supports broadcasting, multicasting, and unicast communication.

## Versions

- **v2.0.0** — created.

---

## Class `shs::UDP`

### Description

`shs::UDP` is a class that manages UDP communication, allowing for the sending and receiving of packets. It inherits from `shs::Process`, enabling it to operate within the event loop of the Smart Home System. The class provides methods for broadcasting, multicasting, and unicast communication.

### Members

- **`UDP_t udp`** — The underlying UDP socket instance, which can be either `WiFiUDP` (for Arduino) or `shs::qt::UdpSocket` (for Qt).

- **`using DTPstatus`** — Alias for the status type from `shs::DTPbus`.

---

### Constructors

- ##### `UDP()`

  ```cpp
  UDP();
  ```

  - ##### Description

    Initializes a `UDP` instance. The constructor is platform-dependent; for Qt, it requires a `new` operator due to QObject inheritance.

---

### Methods

#### Broadcast Methods

- ##### `static uint8_t sendBroadcastPacket(udp, packet, port)`

  ```cpp
  static uint8_t sendBroadcastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Sends a broadcast packet to the specified port.

  - ##### Parameters

    - `udp` — The UDP socket instance.
    - `packet` — The DTP packet to send.
    - `port` — The port number (default is `DEFAULT_UDP_PORT`).

  - ##### Returns

    The result of the send operation.

---

- ##### `uint8_t sendBroadcastRAW(...)`

  ```cpp
  static uint8_t sendBroadcastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Sends raw data as a broadcast.

  - ##### Parameters

    - `udp` — The UDP socket instance.
    - `bc` — The byte collector containing the data to send.
    - `port` — The port number (default is `DEFAULT_UDP_PORT`).

  - ##### Returns

    The result of the send operation.

---

#### Multicast Methods

- ##### `static uint8_t sendMulticastPacket(...)`

  ```cpp
  static uint8_t sendMulticastPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Sends a multicast packet to the specified multicast IP and port.

  - ##### Parameters

    - `udp` — The UDP socket instance.
    - `packet` — The DTP packet to send.
    - `multicastIP` — The multicast IP address (default is `DEFAULT_MULTICAST_IP`).
    - `port` — The port number (default is `DEFAULT_UDP_PORT`).

  - ##### Returns

    The result of the send operation.

---

- ##### `uint8_t sendMulticastRAW(...)`

  ```cpp
  static uint8_t sendMulticastRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t multicastIP = shs::settings::DEFAULT_MULTICAST_IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Sends raw data as a multicast.

  - ##### Parameters

    - `udp` — The UDP socket instance.
    - `bc` — The byte collector containing the data to send.
    - `multicastIP` — The multicast IP address (default is `DEFAULT_MULTICAST_IP`).
    - `port` — The port number (default is `DEFAULT_UDP_PORT`).

  - ##### Returns

    The result of the send operation.

---

#### Unicast Methods

- ##### `static uint8_t sendPacket(...)`

  ```cpp
  static uint8_t sendPacket(UDP_t& udp, const shs::DTPpacket& packet, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Sends a unicast packet to the specified IP and port.

  - ##### Parameters

    - `udp` — The UDP socket instance.
    - `packet` — The DTP packet to send.
    - `IP` — The destination IP address.
    - `port` — The port number (default is `DEFAULT_UDP_PORT`).

  - ##### Returns

    The result of the send operation.

---

- ##### `uint8_t sendRAW(...)`

  ```cpp
  static uint8_t sendRAW(UDP_t& udp, shs::ByteCollector<>& bc, const shs::t::shs_IP_t IP, const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Sends raw data as a unicast.

  - ##### Parameters

    - `udp` — The UDP socket instance.
    - `bc` — The byte collector containing the data to send.
    - `IP` — The destination IP address.
    - `port` — The port number (default is `DEFAULT_UDP_PORT`).

  - ##### Returns

    The result of the send operation.

---

### Process Methods

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the UDP process (currently does nothing).

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Processes incoming UDP packets (if applicable).

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the UDP process (currently does nothing).

---

### Example Usage

```cpp
shs::UDP udp;                       // Create a UDP instance
udp.sendBroadcastPacket(myPacket);  // Send a broadcast packet
```

---

## Conclusion

The `shs::UDP` class provides a comprehensive interface for managing UDP communication within the Smart Home System. With support for broadcasting, multicasting, and unicast, it facilitates efficient data transmission between devices in the network.
