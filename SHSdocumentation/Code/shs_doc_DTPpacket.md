# shs_DTPpacket.h

## General Description

This file contains the definition of the `shs::DTPpacket` class, which is a component of the Smart Home System Data Transfer Protocol (SHSDTP). The class is responsible for creating, encrypting, and decrypting messages, facilitating secure and efficient communication within the system.

## Versions

- **v2.0.0** — created a new component of DTP.

---

## Class `shs::DTPpacket`

### Description

`shs::DTPpacket` is a class designed to handle the creation and processing of data packets within the Smart Home System. It provides constructors for both creating new packets and decoding existing ones, ensuring that packets are constructed and interpreted correctly.

### Members

- `shs::ByteCollector<> bc` — byte collector used for storing packet data.
- `static constexpr auto DTPstandard_OFFSETbeg` — offset for standard packets.
- `static constexpr auto DTPfast_OFFSETbeg` — offset for fast packets.

---

### Constructors

- ##### `DTPpacket()`

  ```cpp
  DTPpacket() noexcept;
  ```

  - ##### Description

    Default constructor that initializes an empty packet.

---

- ##### `DTPpacket(senderID, recipientID, data)`

  ```cpp
  explicit DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, shs::ByteCollector<>&& data) noexcept;
  explicit DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const shs::ByteCollector<>& data) noexcept;
  explicit DTPpacket(const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID, const uint8_t* data, const uint8_t size) noexcept;
  ```

  - ##### Description

    Constructs a packet with the specified sender and recipient IDs, using either a byte collector or raw data.

  - ##### Parameters

    - `senderID` — the ID of the sender.
    - `recipientID` — the ID of the recipient.
    - `data` — the data to include in the packet, provided as a byte collector or raw data array.
    - `size` — the size of the raw data array.

---

- ##### `DTPpacket(data, size)`

  ```cpp
  explicit DTPpacket(const uint8_t* data, const uint8_t size) noexcept;
  ```

  - ##### Description

    Constructs a packet from raw data, typically used for decoding existing packets.

  - ##### Parameters

    - `data` — the raw data array representing the packet.
    - `size` — the size of the raw data array.

---

- ##### `DTPpacket(bc_data)`

  ```cpp
  explicit DTPpacket(shs::ByteCollector<>&& bc_data) noexcept;
  explicit DTPpacket(const shs::ByteCollector<>& bc_data) noexcept;
  ```

  - ##### Description

    Constructs a packet from a byte collector, typically used for decoding existing packets.

  - ##### Parameters

    - `bc_data` — the byte collector containing the packet data.

---

### Methods

- ##### `uint8_t get_DTPcode()`

  ```cpp
  [[nodiscard]] uint8_t get_DTPcode() const;
  ```

  - ##### Description

    Retrieves the DTP code from the packet, indicating the type of message.

  - ##### Returns

    The DTP code as a `uint8_t`.

---

- ##### `shs::t::shs_ID_t get_senderID()`

  ```cpp
  [[nodiscard]] shs::t::shs_ID_t get_senderID() const;
  ```

  - ##### Description

    Retrieves the sender ID from the packet.

  - ##### Returns

    The sender ID.

---

- ##### `shs::t::shs_ID_t get_recipientID()`

  ```cpp
  [[nodiscard]] shs::t::shs_ID_t get_recipientID() const;
  ```

  - ##### Description

    Retrieves the recipient ID from the packet.

  - ##### Returns

    The recipient ID.

---

- ##### `uint8_t check()`

  ```cpp
  [[nodiscard]] uint8_t check() const;
  ```

  - ##### Description

    Checks the integrity of the packet, verifying its size and CRC.

  - ##### Returns

    An error code indicating the result of the check.

---

- ##### `bool empty()`

  ```cpp
  [[nodiscard]] bool empty() const;
  ```

  - ##### Description

    Checks if the packet is empty.

  - ##### Returns

    `true` if the packet is empty, `false` otherwise.

---

### Overloaded Operators

- ##### `operator bool()`

  ```cpp
  operator bool() const;
  ```

  - ##### Description

    Allows the packet to be used in boolean contexts, returning `true` if the packet is not empty.

---

- ##### `operator=`

  ```cpp
  DTPpacket& operator=(DTPpacket&& other) noexcept;
  DTPpacket& operator=(const DTPpacket& other) noexcept;
  ```

  - ##### Description

    Assigns the contents of another packet to this packet, supporting both move and copy semantics.

  - ##### Parameters

    - `other` — the packet to assign from.

---

### Static Functions

- ##### `uint8_t get_DTPcode(it)`

  ```cpp
  [[nodiscard]] static uint8_t get_DTPcode(shs::ByteCollectorReadIterator<> it);
  ```

  - ##### Description

    Retrieves the DTP code from a byte collector iterator.

  - ##### Parameters

    - `it` — the byte collector read iterator.

  - ##### Returns

    The DTP code as a uint8_t.

---

- ##### `shs::t::shs_ID_t get_senderID(it)`

  ```cpp
  [[nodiscard]] static shs::t::shs_ID_t get_senderID(shs::ByteCollectorReadIterator<> it);
  ```

  - ##### Description

    Retrieves the sender ID from a byte collector iterator.

  - ##### Parameters

    - `it` — the byte collector read iterator.

  - ##### Returns

    The sender ID.

---

- ##### `shs::t::shs_ID_t get_recipientID(it)`

  ```cpp
  [[nodiscard]] static shs::t::shs_ID_t get_recipientID(shs::ByteCollectorReadIterator<> it);
  ```

  - ##### Description

    Retrieves the recipient ID from a byte collector iterator.

  - ##### Parameters

    - `it` — the byte collector read iterator.

  - ##### Returns

    The recipient ID.

---

- ##### `uint8_t check(it)`

  ```cpp
  [[nodiscard]] static uint8_t check(shs::ByteCollectorReadIterator<> it);
  ```

  - ##### Description

    Checks the integrity of a packet using a byte collector iterator, verifying its size and CRC.

  - ##### Parameters

    - `it` — the byte collector read iterator.

  - ##### Returns

    An error code indicating the result of the check.

---

### Example Usage

```cpp
shs::DTPpacket packet(senderID, recipientID, data);  // Create a packet with specified IDs and data
auto code = packet.get_DTPcode();                    // Retrieve the DTP code
```

---

## Conclusion

The `shs::DTPpacket` class is a vital component of the Smart Home System, enabling the creation and processing of data packets. Its constructors and methods ensure that packets are constructed and interpreted correctly, facilitating secure and efficient communication within the system.
