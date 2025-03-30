# shs_qt_Udp.h

## General Description

This file contains the definition of the `shs::qt::UdpSocket` class, which serves as a wrapper around the Qt `QUdpSocket` class. The `UdpSocket` class provides an interface for UDP communication, allowing for sending and receiving datagrams within the Smart Home System using the Qt framework.

## Versions

- **v2.0.0** — created, debugged, and tested.

---

## Class `shs::qt::UdpSocket`

### Description

`shs::qt::UdpSocket` is a class that encapsulates the functionality of the Qt `QUdpSocket`, providing methods for binding to a port, sending and receiving UDP datagrams, and managing multicast groups. It emits signals for data reception and errors, allowing for easy integration with Qt's signal-slot mechanism.

### Members

- **`QUdpSocket* m_socket`** — Pointer to the underlying Qt UDP socket instance.
- **`shs::ByteCollector<> m_buf`** — Buffer for managing incoming data.

---

### Constructors

- ##### `UdpSocket(parent)`

  ```cpp
  explicit UdpSocket(QObject* parent = nullptr);
  ```

  - ##### Description

    Initializes a `UdpSocket` instance with an optional parent QObject.

  - ##### Parameters

    - `parent` — The parent QObject for the socket (default is `nullptr`).

---

### Destructor

- ##### `~UdpSocket()`

  ```cpp
  ~UdpSocket() = default;
  ```

  - ##### Description

    Destructor for the `UdpSocket` class.

---

### Methods

- ##### `void begin(port)`

  ```cpp
  void begin(const shs::t::shs_port_t port = shs::settings::DEFAULT_UDP_PORT);
  ```

  - ##### Description

    Binds the UDP socket to the specified port.

  - ##### Parameters

    - `port` — The port number to bind to (default is `DEFAULT_UDP_PORT`).

---

- ##### `void stop()`

  ```cpp
  void stop();
  ```

  - ##### Description

    Closes the UDP socket.

---

- ##### `uint8_t write(buf, size, ip, port)`

  ```cpp
  uint8_t write(const uint8_t* buf, const uint16_t size, const shs::t::shs_IP_t ip, const shs::t::shs_port_t port);
  ```

  - ##### Description

    Sends a datagram to the specified IP address and port.

  - ##### Parameters

    - `buf` — Pointer to the data buffer to send.
    - `size` — Size of the data to send.
    - `ip` — The destination IP address.
    - `port` — The destination port number.

  - ##### Returns

    The number of bytes written.

---

- ##### `uint8_t read()`

  ```cpp
  uint8_t read();
  ```

  - ##### Description

    Reads a single byte of data from the socket.

  - ##### Returns

    The byte read from the socket.

---

- ##### `uint8_t read(buf, size)`

  ```cpp
  uint8_t read(uint8_t* buf, const uint16_t size);
  ```

  - ##### Description

    Reads data from the socket into the provided buffer.

  - ##### Parameters

    - `buf` — Pointer to the buffer where the data will be stored.
    - `size` — Size of the buffer.

  - ##### Returns

    The number of bytes read.

---

- ##### `uint8_t available()`

  ```cpp
  uint8_t available();
  ```

  - ##### Description

    Checks the number of bytes available to read from the socket.

  - ##### Returns

    The number of bytes available.

---

- ##### `void processDatagrams()`

  ```cpp
  void processDatagrams();
  ```

  - ##### Description

    Processes incoming datagrams and stores them in the buffer.

---

- ##### `bool joinMulticastGroup(groupIP)`

  ```cpp
  bool joinMulticastGroup(const shs::t::shs_IP_t groupIP);
  ```

  - ##### Description

    Joins a multicast group with the specified IP address.

  - ##### Parameters

    - `groupIP` — The multicast IP address to join.

  - ##### Returns

    `true` if successfully joined; otherwise, `false`.

---

- ##### `bool leaveMulticastGroup(groupIP)`

  ```cpp
  bool leaveMulticastGroup(const shs::t::shs_IP_t groupIP);
  ```

  - ##### Description

    Leaves a multicast group with the specified IP address.

  - ##### Parameters

    - `groupIP` — The multicast IP address to leave.

  - ##### Returns

    `true` if successfully left; otherwise, `false`.

---

### Signals

- ##### `void dataReceived()`

  - Emitted when data is received from the socket.

- ##### `void error(const QString& errorString)`

  - Emitted when an error occurs with the socket, providing the error message.

---

### Private Slots

- ##### `void onReadyRead()`

  - Slot to handle the ready read signal from the underlying QTcpSocket, processing incoming datagrams.

- ##### `void onError(QAbstractSocket::SocketError socketError)`

  - Slot to handle error signals from the underlying QTcpSocket.

---

## Conclusion

The `shs::qt::UdpSocket` class provides a convenient wrapper around the Qt `QUdpSocket`, aligning its interface with the UDP communication needs of the Smart Home System. This allows for easy integration of UDP functionality while leveraging the capabilities of the Qt framework.
