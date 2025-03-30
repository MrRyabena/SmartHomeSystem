# shs_TcpSocket.h

## General Description

This file contains the definition of the `shs::TcpSocket` class, which provides a TCP socket implementation for communication within the Smart Home System. The class is built on top of `shs::DTPbus` and includes features such as automatic reconnection in case of connection loss.

## Versions

- **v0.1.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — updated functionality, debugged, tested.
  - It is based on `shs::DTPbus`.
  - Automatic reconnection in case of loss of connection.
  - Qt support.

---

## Class `shs::TcpSocket`

### Description

`shs::TcpSocket` is a class that manages TCP socket connections for the Smart Home System. It provides methods for connecting, sending, and receiving data over TCP, while ensuring that the connection remains active and can automatically reconnect if it is lost.

### Members

- `shs::t::shs_IP_t m_hostIP` — The IP address of the host to connect to.
- `shs::t::shs_port_t m_port` — The port number to connect to on the host.
- `bool m_active_flag` — A flag indicating whether the socket is active.
- `std::function<void(shs::TcpSocket&)> m_connect_callback` — Callback function to be called upon successful connection.
- `std::function<void(shs::TcpSocket&)> m_disconnect_callback` — Callback function to be called upon disconnection.

---

### Constructors

- ##### `TcpSocket(hostIP, port, busID, handler, bufsize, connect_callback, disconnect_callback)`

  ```cpp
  explicit TcpSocket
  (
      const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
      const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
      const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
      const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
  );
  ```

  - ##### Description

    Initializes a `TcpSocket` instance with the specified host IP, port, bus ID, and optional callback functions for connection and disconnection events.

  - ##### Parameters

    - `hostIP` — The IP address of the host.
    - `port` — The port number to connect to.
    - `busID` — The bus ID for the DTP communication.
    - `handler` — Optional API handler for processing incoming messages.
    - `bufsize` — Size of the buffer for DTP communication (default is 25).
    - `connect_callback` — Callback function for successful connection (default is `default_connect_callback`).
    - `disconnect_callback` — Callback function for disconnection (default is `default_disconnect_callback`).

---

- ##### `TcpSocket(parent, hostIP, port, busID, handler, bufsize, connect_callback, disconnect_callback)`

  ```cpp
  explicit TcpSocket
  (
  #ifdef SHS_SF_ARDUINO
      const WiFiClient& parent,
  #elif defined(SHS_SF_QT)
      QObject* parent,
      const shs::t::shs_IP_t& hostIP, const shs::t::shs_port_t port,
  #endif
      const shs::t::shs_busID_t busID, shs::API* handler = nullptr, const uint8_t bufsize = 25,
      const std::function<void(shs::TcpSocket&)>& connect_callback = default_connect_callback,
      const std::function<void(shs::TcpSocket&)>& disconnect_callback = default_disconnect_callback
  );
  ```

  - ##### Description

    Initializes a `TcpSocket` instance with a specified parent object (for Qt or Arduino), host IP, port, bus ID, and optional callback functions.

  - ##### Parameters

    - `parent` — The parent object for the socket (either `WiFiClient` for Arduino or `QObject` for Qt).
    - `hostIP` — The IP address of the host.
    - `port` — The port number to connect to.
    - `busID` — The bus ID for the DTP communication.
    - `handler` — Optional API handler for processing incoming messages.
    - `bufsize` — Size of the buffer for DTP communication (default is 25).
    - `connect_callback` — Callback function for successful connection (default is `default_connect_callback`).
    - `disconnect_callback` — Callback function for disconnection (default is `default_disconnect_callback`).

---

### Destructor

- ##### `~TcpSocket()`

  ```cpp
  ~TcpSocket() = default;
  ```

  - ##### Description

    Destructor for the `TcpSocket` class.

---

### Methods

- ##### `void reconnect()`

  ```cpp
  void reconnect();
  ```

  - ##### Description

    Attempts to reconnect the TCP socket if the connection is lost.

---

- ##### `shs::t::shs_IP_t getIP() const`

  ```cpp
  shs::t::shs_IP_t getIP() const;
  ```

  - ##### Description

    Retrieves the IP address of the host.

  - ##### Returns

    The host IP address.

---

- ##### `shs::t::shs_port_t getPort() const`

  ```cpp
  shs::t::shs_port_t getPort() const;
  ```

  - ##### Description

    Retrieves the port number of the host.

  - ##### Returns

    The host port number.

---

- ##### `void setActive(const bool flag)`

  ```cpp
  void setActive(const bool flag);
  ```

  - ##### Description

    Sets the active state of the TCP socket.

  - ##### Parameters

    - `flag` — `true` to activate the socket, `false` to deactivate.

---

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the TCP socket and attempts to connect to the host.

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Checks the connection status and calls the disconnect callback if the client is not connected.

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the TCP socket and disconnects from the host.

---

- ##### `bool isActive() const override`

  ```cpp
  bool isActive() const override;
  ```

  - ##### Description

    Checks if the TCP socket is active.

  - ##### Returns

    `true` if the socket is active; otherwise, `false`.

---

- ##### `Status checkBus() override`

  ```cpp
  Status checkBus() override;
  ```

  - ##### Description

    Checks the status of the DTP bus.

  - ##### Returns

    The status of the bus.

---

- ##### `uint8_t sendPacket(const shs::DTPpacket& packet) override`

  ```cpp
  uint8_t sendPacket(const shs::DTPpacket& packet) override;
  ```

  - ##### Description

    Sends a DTP packet over the TCP socket.

  - ##### Parameters

    - `packet` — The DTP packet to send.

  - ##### Returns

    The result of the send operation.

---

- ##### `uint8_t sendRAW(shs::ByteCollector<>& bc) override`

  ```cpp
  uint8_t sendRAW(shs::ByteCollector<>& bc) override;
  ```

  - ##### Description

    Sends raw data over the TCP socket.

  - ##### Parameters

    - `bc` — The byte collector containing the data to send.

  - ##### Returns

    The result of the send operation.

---

- ##### `uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override`

  ```cpp
  uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override;
  ```

  - ##### Description

    Sends raw data over the TCP socket using an iterator.

  - ##### Parameters

    - `it` — The iterator pointing to the data to send.

  - ##### Returns

    The result of the send operation.

---

- ##### `uint8_t sendRAW(const uint8_t* data, const uint8_t size) override`

  ```cpp
  uint8_t sendRAW(const uint8_t* data, const uint8_t size) override;
  ```

  - ##### Description

    Sends raw data over the TCP socket.

  - ##### Parameters

    - `data` — Pointer to the data to send.
    - `size` — Size of the data to send.

  - ##### Returns

    The result of the send operation.

---

### Example Usage

```cpp
shs::TcpSocket tcpSocket("192.168.1.1", 8080, busID);   // Create a TcpSocket instance
tcpSocket.start();                                      // Start the socket and connect to the host
```

---

## Conclusion

The `shs::TcpSocket` class provides a robust implementation for managing TCP socket connections in the Smart Home System. With features like automatic reconnection and support for both Arduino and Qt, it facilitates reliable communication between devices, ensuring seamless operation within the system.
