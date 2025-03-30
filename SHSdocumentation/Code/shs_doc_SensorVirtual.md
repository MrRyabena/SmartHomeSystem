# shs_SensorVirtual.h

## General Description

This file contains the definition of the `shs::SensorVirtual` class, which provides access to a remote sensor located on another device through the `shs::Sensor` interface. The class allows for interaction with virtual sensors, enabling the Smart Home System to manage sensor data from various sources seamlessly.

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — moved to a separate file, redesigned, debugged, and tested.

---

## Class `shs::SensorVirtual`

### Description

`shs::SensorVirtual` is a class that extends the functionality of the `shs::Sensor` class, allowing it to represent a virtual sensor. This class facilitates communication with remote sensors, enabling the Smart Home System to retrieve and manage sensor data effectively.

### Members

- `shs::t::shs_ID_t m_virtualID` — ID of the virtual sensor instance.
- `shs::DTP& m_dtp` — Reference to the DTP instance used for communication with the remote sensor.
- `shs::t::shs_fixed_t m_value` — Stores the current value of the sensor.
- `bool m_updatedFlag` — Flag indicating whether the sensor value has been updated.

---

### Constructor

- ##### `SensorVirtual(thisID, virtualID, dtp, stype)`

  ```cpp
  explicit SensorVirtual(shs::t::shs_ID_t thisID, shs::t::shs_ID_t virtualID, shs::DTP& dtp, const shs::Sensor::Type stype = UNKNOWN);
  ```

  - ##### Description

    Initializes a `SensorVirtual` instance with specified IDs, DTP instance, and sensor type.

  - ##### Parameters

    - `thisID` — The ID of the current sensor instance.
    - `virtualID` — The ID of the virtual sensor.
    - `dtp` — Reference to the DTP instance for communication.
    - `stype` — The type of the sensor (default is `UNKNOWN`).

---

### Methods

- ##### `shs::DTPpacket handle(it)`

  ```cpp
  shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
  ```

  - ##### Description

    Handles incoming messages and executes the corresponding command for the virtual sensor.

  - ##### Parameters

    - `it` — The byte collector read iterator containing the incoming message.

  - ##### Returns

    A DTP packet containing the response to the command.

---

- ##### `void setup()`

  ```cpp
  void setup() override;
  ```

  - ##### Description

    Sets up the virtual sensor. This method can be overridden to implement specific setup behavior.

---

- ##### `void update()`

  ```cpp
  void update() override;
  ```

  - ##### Description

    Updates the state of the virtual sensor, retrieving the latest data from the remote source.

---

- ##### `void updateFast()`

  ```cpp
  void updateFast() override;
  ```

  - ##### Description

    Performs a fast update of the virtual sensor state, optimizing for speed.

---

- ##### `bool isUpdated()`

  ```cpp
  [[nodiscard]] bool isUpdated() override;
  ```

  - ##### Description

    Checks if the sensor value has been updated since the last retrieval.

  - ##### Returns

    `true` if the sensor value has been updated; otherwise, `false`.

---

- ##### `uint8_t getStatus()`

  ```cpp
  [[nodiscard]] uint8_t getStatus() override;
  ```

  - ##### Description

    Retrieves the current status of the virtual sensor.

  - ##### Returns

    The status code of the sensor.

---

- ##### `int32_t getValueI(metric)`

  ```cpp
  [[nodiscard]] int32_t getValueI([[maybe_unused]] const uint8_t metric = 0) override;
  ```

  - ##### Description

    Retrieves the current value of the sensor as an integer.

  - ##### Parameters

    - `metric` — Optional metric parameter (default is 0).

  - ##### Returns

    The current sensor value as an integer.

---

- ##### `shs::t::shs_fixed_t getValueFx(metric)`

  ```cpp
  [[nodiscard]] shs::t::shs_fixed_t getValueFx([[maybe_unused]] const uint8_t metric = 0) override;
  ```

  - ##### Description

    Retrieves the current value of the sensor as a fixed-point number.

  - ##### Parameters

    - `metric` — Optional metric parameter (default is 0).

  - ##### Returns

    The current sensor value as a fixed-point number.

---

- ##### `shs::t::shs_float_t getValueF(metric)`

  ```cpp
  [[nodiscard]] shs::t::shs_float_t getValueF([[maybe_unused]] const uint8_t metric = 0) override;
  ```

  - ##### Description

    Retrieves the current value of the sensor as a floating-point number.

  - ##### Parameters

    - `metric` — Optional metric parameter (default is 0).

  - ##### Returns

    The current sensor value as a floating-point number.

---

- ##### `shs::t::shs_double_t getValueD(metric)`

  ```cpp
  [[nodiscard]] shs::t::shs_double_t getValueD([[maybe_unused]] const uint8_t metric = 0) override;
  ```

  - ##### Description

    Retrieves the current value of the sensor as a double-precision floating-point number.

  - ##### Parameters

    - `metric` — Optional metric parameter (default is 0).

  - ##### Returns

    The current sensor value as a double-precision floating-point number.

---

## Conclusion

The `shs::SensorVirtual` class is a crucial component of the Smart Home System, providing a flexible interface for accessing remote sensors. Its methods enable efficient data retrieval and management, ensuring seamless integration of sensor data from various devices.
