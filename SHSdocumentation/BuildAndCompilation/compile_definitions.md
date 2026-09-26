# SHScore compile definitions

- [Debug](#debug)
- [Compilation and Includies](#compilation-and-includes)
  - [Platforms flags](#platforms-flags)
- [Network](#network)
  - [Enable](#enable)
  - [WiFi](#wifi)
  - [IP and Ports](#ip-and-ports)
- [Optimizations](#optimizations)
- [Qt](#qt)
- [Time Settings](#time-settings)

---

If you need to define compile-time macros, you can use one of the following methods:

- Create `shs_settings.h`. It will be included by `SHScore/shs_settings_private.h`.
- Use CMake with `set_compile_definitions(...)`
- Pass definitions to the compiler using `-D...`
- Use PlatformIO with `build_definitions = -D ...`

## Debug

```cpp
SHS_SF_DEBUG    // Enable debugging outputs
```

> [!IMPORTANT]
> Enabling this flag may increase code size and firmware size due to additional debug information.

## Compilation and Includes

```cpp
SHS_SF_UNUSE_SHS_SETTINGS    // Do not include `shs_settings.h` if this file cannot be added to the build.
```

### Platform-Specific Flags

These flags are usually defined by the development environment (PlatformIO, Arduino IDE, compiler toolchains, etc.) and are used for platform integration.

> [!WARNING]
> You only need to define these flags if you are using a custom development environment or if your environment does not define them automatically.
>

- `ESP8266`
- `ESP32`
- `__AVR__`

## Network

### Enable

```cpp
SHS_SF_NETWORK    // Enables Network in SHScore and SHSlibrary
```

### WiFi

```cpp
SHS_SET_WIFI_CONFIGS     // Set WiFi configurations
SHS_SET_WIFI_SSID        // Set the default WiFi SSID
SHS_SET_WIFI_PASSWORD    // Set the default WiFi PASSWORD
```

```cpp
// Usage:

#include <shs_WiFiConfig.h>
#include <iterator>

#define SHS_SET_WIFI_CONFIGS
namespace shs::settings
{
    static constexpr shs::WiFiConfig WiFiConfigs[] = {
        {"SSID_1", "password_1"},
        {"SSID_2", "password_2"},
        {"SSID_3", "password_3"},
        {"SSID_4", "password_4"},
        // ...
    };

        static constexpr auto WiFiConfigs_size = std::size(WiFiConfigs);
}

// or

#define SET_WIFI_SSID     "Your_SSID"
#define SET_WIFI_PASSWORD "Your_PASSWORD"
```

### IP and Ports

```cpp
SHS_SET_SENSOR_AVERAGE_SAMPLE    //default: 20
SHS_SET_DEFAULT_TCP_PORT         // default: 5000
SHS_SET_DEFAULT_UDP_PORT         // default: 6000
SHS_SET_DEFAULT_MULTICAST_IP     // default: "224.0.0.4"
SHS_SET_DEFAULT_BROADCAST_IP     // default: "192.168.1.255"
```

## Optimizations

```cpp
USE_FLOAT_FOR_DOUBLE    // All shs::t::shs_double_t will be equal shs::t::shs_float_t that is equal `float`. May be used for optimizations for microcontrollers or the speceific processors
```

## Qt

```cpp
SHS_QT_FLAG    // Enable QT in components that can it use
```

## Time Settings

```cpp
SHS_SET_GMT    // Set the Greenwich Mean Time (UTC), default is 0
```
