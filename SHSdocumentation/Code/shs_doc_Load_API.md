# shs_Load_API.h

## General Description

This file contains the definition of the `shs::Load_API` class, which serves as a handler for controlling loads within the Smart Home System. The class provides an interface for sending commands to loads and processing incoming messages.

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — redesigned, debugged, and tested.

---

## Class `shs::Load_API`

### Description

`shs::Load_API` is a class that acts as an interface for controlling load devices. It processes commands received from the network and interacts with the associated load to perform actions such as turning it on or off and retrieving its current value.

### Members

- `enum Commands` — Defines the commands that can be sent to the load:
  - `ON8` — Command to turn on the load with an 8-bit value.
  - `ON16` — Command to turn on the load with a 16-bit value.
  - `OFF` — Command to turn off the load.
  - `GET_VALUE` — Command to request the current value of the load.
  - `VALUE` — Response command that includes the current value of the load.

---

### Constructor

- ##### `Load_API(load, ID)`

  ```cpp
  Load_API(shs::Load& load, shs::t::shs_ID_t ID) noexcept;
  ```

  - ##### Description

    Initializes a Load_API instance with a specified load and module ID.

  - ##### Parameters

    - `load` — Reference to the load instance to control.
    - `ID` — The ID of the API instance.

---

### Methods

- ##### `shs::DTPpacket handle(it)`

  ```cpp
  [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;
  ```

  - ##### Description

    Handles incoming messages and executes the corresponding command on the load.

  - ##### Parameters

    - `it` — The byte collector read iterator containing the incoming message.

  - ##### Returns

    A DTP packet containing the response to the command.

---

### Example Usage

```cpp
#include <memory>

#include <shs_Network.hpp>
#include <shs_DTP.hpp>

#include <shs_Load.hpp>

#define SHS_SF_DEBUG
#include <shs_debug.h>

shs::LoadSwitchReversed load(LED_BUILTIN);


shs::DTP dtp(shs::config::Module_2::MODULE_ID);
shs::TcpServer server(shs::settings::DEFAULT_TCP_PORT, dtp);
shs::DTPdiscover discover(shs::config::Module_2::MODULE_ID);


void setup()
{
  Serial.begin(115200);
doutln("");
  
    doutln(shs::ControlWiFi::connectWiFiWait());

    load.setup();
    load.off();

    dtp.attachAPI(std::make_unique<shs::Load_API>(load, shs::t::shs_ID_t(shs::config::Module_2::MODULE_ID, shs::config::Module_2::LOAD)));

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

The `shs::Load_API` class is an essential component of the Smart Home System, providing a robust interface for controlling load devices. Its methods facilitate the processing of commands and the management of load states, ensuring efficient operation within the system.
