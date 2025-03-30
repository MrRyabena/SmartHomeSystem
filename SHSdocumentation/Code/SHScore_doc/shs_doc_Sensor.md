# shs_Sensor.h

## General Description

This file contains the definition of the `shs::Sensor` class, which serves as an abstract base class for various sensor types within the Smart Home System. The class provides a common interface for sensor functionality, enabling efficient data acquisition and management.

## Included Components

> in headers <shs_Sensor> and <shs_Sensor.hpp>

This file includes the following components related to the `shs::Sensor` class:

- **`shs_Sensor.h`** — Main header file for the sensor interface, defining the abstract class `shs::Sensor` and its methods for managing various types of sensors.

- **`shs_Sensor_API.h`** — Contains the API definitions for interacting with sensor components, providing methods for handling sensor data and commands.

- **`shs_SensorAnalog.h`** — Defines the `shs::SensorAnalog` class, which implements the interface for analog sensors, allowing for reading values from analog input pins.

- **`shs_SensorVirtual.h`** — Defines the class, which represents a virtual sensor that can receive data from a remote device.

## Versions

- **v0.1.0** — created.
- **v0.2.0** — made purely virtual.
- **v1.0.0** — release.
- **v2.0.0** — redesigned, debugged, and tested.
  - The functionality has been changed.
  - `update()` must be called before getting the value.
  - `updateFast()`, if supported by the sensor, measures less accurately but faster.
  - Added error status.
  - Support for multiple metrics.
  - Caching support.

---

## Class `shs::Sensor`

### Description

`shs::Sensor` is an abstract class that defines the interface for sensors in the Smart Home System. It provides methods for setting up sensors, updating their readings, and retrieving values. The class supports various sensor types and allows for caching of sensor data.

### Members

- `enum Type` — Defines the different types of sensors:
  - `UNKNOWN` — Represents an unknown sensor type.
  - `ANALOG_PIN` — Represents an analog pin sensor.
  - `THERMISTOR` — Represents a thermistor sensor.
  - `PHOTORESISTOR` — Represents a photoresistor sensor.
  - `DIGITAL` — Represents a digital sensor.
  - `LIBRARY_TYPES` — Reserved for library-defined sensor types.
  - `USER_TYPES` — Reserved for user-defined sensor types.

---

### Constructor

- ##### `Sensor(stype)`

  ```cpp
  explicit Sensor(const Type stype = UNKNOWN);
  ```

  - ##### Description

    Initializes a Sensor instance with a specified sensor type.

  - ##### Parameters

    - `stype` — The type of the sensor (default is `UNKNOWN`).

---

### Destructor

- ##### `~Sensor()`

  ```cpp
  virtual ~Sensor() = default;
  ```

  - ##### Description

    Cleans up resources used by the Sensor instance.

---

### Methods

- ##### `void setup()`

  ```cpp
  virtual void setup() = 0;
  ```

  - ##### Description

    Sets up the sensor. This method must be implemented by derived classes.

---

- ##### `void update()`

  ```cpp
  virtual void update() = 0;
  ```

  - ##### Description

    Updates the sensor's readings. This method must be implemented by derived classes.

---

- ##### `void updateFast()`

  ```cpp
  virtual void updateFast() = 0;
  ```

  - ##### Description

    Updates the sensor's readings quickly, potentially with less accuracy. This method must be implemented by derived classes.

---

- ##### `void updateForced(fast)`

  ```cpp
  virtual void updateForced(bool fast = false) = 0;
  ```

  - ##### Description

    Forces an update of the sensor's readings, with an option for fast updating. This method must be implemented by derived classes.

---

- ##### `bool isUpdated()`

  ```cpp
  [[nodiscard]] virtual bool isUpdated() = 0;
  ```

  - ##### Description

    Checks if the sensor has been updated since the last reading.

  - ##### Returns

    `true` if the sensor has been updated, `false` otherwise.

---

- ##### `uint8_t getStatus()`

  ```cpp
  [[nodiscard]] virtual uint8_t getStatus() = 0;
  ```

  - ##### Description

    Retrieves the current status of the sensor.

  - ##### Returns

    The status of the sensor as a uint8_t.

---

- ##### `int32_t getValueI(metric)`

  ```cpp
  [[nodiscard]] virtual int32_t getValueI(const uint8_t metric = 0) = 0;
  ```

  - ##### Description

    Retrieves the integer value of the sensor reading for the specified metric.

  - ##### Parameters

    - `metric` — The metric to retrieve (default is 0).

---

- ##### `shs::t::shs_fixed_t getValueFx(metric)`

  ```cpp
  [[nodiscard]] virtual shs::t::shs_fixed_t getValueFx(const uint8_t metric = 0) = 0;
  ```

  - ##### Description

    Retrieves the fixed-point value of the sensor reading for the specified metric.

  - ##### Parameters

    - `metric` — The metric to retrieve (default is 0).

---

- ##### `shs::t::shs_float_t getValueF(metric)`

  ```cpp
  [[nodiscard]] virtual shs::t::shs_float_t getValueF(const uint8_t metric = 0) = 0;
  ```

  - ##### Description

    Retrieves the floating-point value of the sensor reading for the specified metric.

  - ##### Parameters

    - `metric` — The metric to retrieve (default is 0).

---

- ##### `shs::t::shs_double_t getValueD(metric)`

  ```cpp
  [[nodiscard]] virtual shs::t::shs_double_t getValueD(const uint8_t metric = 0) = 0;
  ```

  - ##### Description

    Retrieves the double-precision value of the sensor reading for the specified metric.

  - ##### Parameters

    - `metric` — The metric to retrieve (default is 0).

---

## Conclusion

The `shs::Sensor` class is a fundamental component of the Smart Home System, providing a robust mechanism for representing and managing various types of sensors. Its methods and constructors facilitate easy manipulation and control of sensor data, ensuring efficient operation within the system.
