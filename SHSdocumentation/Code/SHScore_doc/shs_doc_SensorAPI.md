# shs_Sensor_API.h

## General Description

This file contains the definition of the `shs::Sensor_API` class, which serves as an interface for managing sensor interactions within the Smart Home System. The class provides methods for handling commands related to sensors and facilitates communication between sensors and the DTP (Data Transfer Protocol).

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — redesigned, debugged, and tested.

---

## Class `shs::Sensor_API`

### Description

`shs::Sensor_API` is a class that acts as a handler for sensor components, allowing for the processing of commands and interaction with the associated sensor. It inherits from both `shs::API` and `shs::Process`, enabling it to manage API requests and operate within the event loop of the Smart Home System.

### Members

- `shs::Sensor& m_sensor` — Reference to the sensor instance being managed.
- `shs::DTP& m_dtp` — Reference to the DTP instance used for communication.
- `std::vector<shs::t::shs_ID_t> m_requestIDs` — Vector to store request IDs for managing multiple requests.

---

### Constructor

- ##### `Sensor_API(sensor, id, dtp)`

  ```cpp
  explicit Sensor_API(shs::Sensor& sensor, shs::t::shs_ID_t id, shs::DTP& dtp) noexcept;
  ```

  - ##### Description

    Initializes a Sensor_API instance with a specified sensor, module ID, and DTP instance.

  - ##### Parameters

    - `sensor` — Reference to the sensor instance to control.
    - `id` — The ID of the API instance.
    - `dtp` — Reference to the DTP instance for communication.

---

### Methods

- ##### `shs::DTPpacket handle(it)`

  ```cpp
  [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
  ```

  - ##### Description

    Handles incoming messages and executes the corresponding command on the associated sensor.

  - ##### Parameters

    - `it` — The byte collector read iterator containing the incoming message.

  - ##### Returns

    A DTP packet containing the response to the command.

---

- ##### `void start()`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the API process. This method can be overridden to implement specific start behavior.

---

- ##### `void tick()`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Updates the state of the Sensor_API instance and processes incoming requests.

---

- ##### `void stop()`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the API process. This method can be overridden to implement specific stop behavior.

---

### Example Usage

```cpp
#include <memory>
#include <shs_debug.h>

#include <shs_Network.hpp>
#include <shs_DTP.hpp>

#include <shs_lib_Thermistor.h>
#include <shs_Sensor_API.h>

shs::Thermistor temp_sensor(A0, 10'000, 3435);

shs::DTP dtp(shs::config::Module_1::MODULE_ID);
shs::TcpServer server(shs::settings::DEFAULT_TCP_PORT, dtp);
shs::DTPdiscover discover(shs::config::Module_1::MODULE_ID);


void setup()
{
    dinit();
    shs::ControlWiFi::connectWiFiWait();

    dtp.attachAPI(std::make_unique<shs::Sensor_API>(temp_sensor, shs::t::shs_ID_t(shs::config::Module_1::MODULE_ID, shs::config::Module_1::DevicesIDs::THERM_SENSOR), dtp));

    dtp.start();
    server.start();
    discover.start();
}


void loop()
{
    dtp.tick();
    server.tick();
    discover.tick();
}

```

---

## Conclusion

The `shs::Sensor_API` class is an essential component of the Smart Home System, providing a robust interface for managing sensor interactions. Its methods facilitate the processing of commands and the management of sensor states, ensuring efficient operation within the system.