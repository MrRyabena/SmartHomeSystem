# shs_qt_TcpSocket.h

## General Description

This file contains the definition of the `shs::qt::TcpSocket` class, which serves as a wrapper around the Qt `QTcpSocket` class. The `TcpSocket` class provides an interface that aligns with the `shs::TcpSocket` class, enabling seamless integration of TCP socket functionality within the Smart Home System using the Qt framework.

## Versions

- **v2.0.0** — created, debugged, and tested.

---

## Class `shs::qt::TcpSocket`

### Description

`shs::qt::TcpSocket` is a class that encapsulates the Qt `QTcpSocket` functionality, providing methods for connecting to hosts, sending and receiving data, and managing socket states. It emits signals for connection events, errors, and data reception, allowing for easy integration with Qt's signal-slot mechanism.

### Members

- `QTcpSocket* m_qtcp_socket` — Pointer to the underlying Qt TCP socket instance.

---

### Constructors

- ##### `TcpSocket(parent)`

  ```cpp
  explicit TcpSocket(QObject* parent = nullptr);
  ```

  - ##### Description

    Initializes a `TcpSocket` instance with an optional parent QObject.

  - ##### Parameters

    - `parent` — The parent QObject for the socket (default is `nullptr`).

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

- ##### `uint8_t write(buf, size)`

  ```cpp
  uint8_t write(const uint8_t* buf, const uint16_t size);
  ```

  - ##### Description

    Sends data to the connected host.

  - ##### Parameters

    - `buf` — Pointer to the data buffer to send.
    - `size` — Size of the data to send.

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

- ##### `bool connectToHost(ip, port)`

  ```cpp
  bool connectToHost(const shs::t::shs_IP_t ip, const shs::t::shs_port_t port);
  ```

  - ##### Description

    Connects to the specified host IP and port.

  - ##### Parameters

    - `ip` — The IP address of the host.
    - `port` — The port number to connect to.

  - ##### Returns

    `true` if the connection was successful; otherwise, `false`.

---

- ##### `void disconnectFromHost()`

  ```cpp
  void disconnectFromHost();
  ```

  - ##### Description

    Disconnects from the currently connected host.

---

- ##### `void stop()`

  ```cpp
  void stop();
  ```

  - ##### Description

    Stops the socket and disconnects from the host.

---

- ##### `bool connected()`

  ```cpp
  bool connected();
  ```

  - ##### Description

    Checks if the socket is currently connected to a host.

  - ##### Returns

    `true` if the socket is connected; otherwise, `false`.

---

### Signals

- ##### `void s_connected()`

  - Emitted when the socket successfully connects to a host.

- ##### `void disconnected()`

  - Emitted when the socket is disconnected from the host.

- ##### `void errorOccurred(const QString& errorString)`

  - Emitted when an error occurs with the socket, providing the error message.

- ##### `void dataReceived()`

  - Emitted when data is received from the connected host.

---

### Private Slots

- ##### `void onConnected()`

  - Slot to handle the connected signal from the underlying QTcpSocket.

- ##### `void onDisconnected()`

  - Slot to handle the disconnectesd signal from the underlying QTcpSocket.

- ##### `void onError(QAbstractSocket::SocketError socketError)`

  - Slot to handle error signals from the underlying QTcpSocket.

- ##### `void onReadyRead()`

  - Slot to handle data ready to be read from the underlying QTcpSocket.

---

## Conclusion

The `shs::qt::TcpSocket` class provides a convenient wrapper around the Qt `QTcpSocket`, aligning its interface with the `shs::TcpSocket` class. This allows for easy integration of TCP socket functionality within the Smart Home System while leveraging the capabilities of the Qt framework.
