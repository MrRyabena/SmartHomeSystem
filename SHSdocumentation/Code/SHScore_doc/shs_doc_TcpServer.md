# shs_TcpServer.h

## General Description

This file contains the definition of the `shs::TcpServer` class, which serves as a server for processing client connections in the Smart Home System. The class is designed to handle incoming TCP connections and automatically attach clients to the `shs::DTP` (Data Transfer Protocol). It also manages client lifecycles, ensuring that clients are deleted when their connections are closed.

## Versions

- **v0.1.0** — created.
- **v0.2.0** — corrected.
- **v1.0.0** — release.
- **v2.0.0** — updated functionality, debugged, tested.
  - Automatically attach clients to `shs::DTP`.
  - Configure clients to delete when the connection is closed.

---

## Class `shs::TcpServer`

### Description

`shs::TcpServer` is a class that manages a TCP server, allowing it to accept and process client connections. It inherits from `shs::Process`, enabling it to operate within the event loop of the Smart Home System. The server automatically handles client connections and integrates with the DTP for data communication.

### Members

- `WiFiServer server` — The underlying WiFi server instance for handling TCP connections.
- `shs::DTP& m_dtp` — Reference to the DTP instance used for managing data transfer with clients.
- `std::unique_ptr<shs::TcpSocket> m_connecting_client` — Pointer to the currently connecting client socket.
- `size_t m_connecting_client_time` — Timer for managing the connection time of the client.

---

### Constructors

- ##### `TcpServer(hostIP, port, dtp)`

  ```cpp
  explicit TcpServer(const IPAddress& hostIP, const uint16_t port, shs::DTP& dtp);
  ```

  - ##### Description

    Initializes a `TcpServer` instance with a specified host IP address and port, along with a reference to the DTP instance.

  - ##### Parameters

    - `hostIP` — The IP address of the server.
    - `port` — The port number on which the server will listen for incoming connections.
    - `dtp` — Reference to the DTP instance for managing data transfer.

---

- ##### `TcpServer(port, dtp)`

  ```cpp
  explicit TcpServer(const uint16_t port, shs::DTP& dtp);
  ```

  - ##### Description

    Initializes a `TcpServer` instance with a specified port and a reference to the DTP instance.

  - ##### Parameters

    - `port` — The port number on which the server will listen for incoming connections.
    - `dtp` — Reference to the DTP instance for managing data transfer.

---

### Destructor

- ##### `~TcpServer()`

  ```cpp
  ~TcpServer() = default;
  ```

  - ##### Description

    Destructor for the `TcpServer` class.

---

### Methods

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the TCP server, allowing it to begin accepting client connections.

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Processes incoming client connections and manages the state of connected clients.

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the TCP server and disconnects all clients.

---

### Example Usage

```cpp
shs::DTP dtp;                                        // Assume dtp is already initialized
shs::TcpServer tcpServer("192.168.1.1", 8080, dtp);  // Create a TcpServer instance
tcpServer.start();                                   // Start the server to accept connections
```

---

## Conclusion

The `shs::TcpServer` class provides a robust implementation for managing TCP server functionality within the Smart Home System. By automatically handling client connections and integrating with the DTP, it ensures efficient communication and management of connected devices.