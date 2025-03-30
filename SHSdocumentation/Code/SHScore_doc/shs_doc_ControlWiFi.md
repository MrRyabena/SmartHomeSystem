# shs_ControlWiFi.h

## General Description

This file contains the definition of the `shs::ControlWiFi` class, which provides a simplified interface for managing WiFi connections on ESP microcontrollers. The class is designed to facilitate common WiFi operations such as connecting to a network, setting hostnames, and managing WiFi states.

## Compatibility

The `shs::ControlWiFi` class is specifically designed to work with ESP family microcontrollers, including ESP8266 and ESP32. It leverages the respective WiFi libraries for these platforms to provide seamless connectivity features.

## Versions

- **v2.0.0** — created for replacing `shs_connectWiFi.h`.

## Class `shs::ControlWiFi`

### Description

`shs::ControlWiFi` is a static class that provides methods for managing WiFi connections on ESP microcontrollers. It includes functionalities for connecting to WiFi networks, configuring settings, and checking connection status.

### Methods

- ##### `bool setHostname(hostname)`

  ```cpp
  static bool setHostname(const char* hostname);
  ```

  - ##### Description

    Sets the hostname for the ESP device.

  - ##### Parameters

    - `hostname` — the hostname to set for the device.

- ##### `void connectWiFi(ssid, pass)`

  ```cpp
  static void connectWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD);
  ```

  - ##### Description

    Initiates a connection to the specified WiFi network using the provided SSID and password.

  - ##### Parameters

    - `ssid` — the SSID of the WiFi network (default is `shs::settings::WIFI_SSID`).
    - `pass` — the password for the WiFi network (default is `shs::settings::WIFI_PASSWORD`).

- ##### `bool connectWiFiWait(time, ssid, pass)`

  ```cpp
  static bool connectWiFiWait(const size_t time = 20000, const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD);
  ```

  - ##### Description

    Connects to the specified WiFi network and waits for the connection to be established within the given time limit.

  - ##### Parameters

    - `time` — the maximum time to wait for connection (default is `20000` milliseconds).
    - `ssid` — the SSID of the WiFi network (default is `shs::settings::WIFI_SSID`).
    - `pass` — the password for the WiFi network (default is `shs::settings::WIFI_PASSWORD`).

- ##### `void configureWiFi(ssid, pass)`

  ```cpp
  static void configureWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD);
  ```

  - ##### Description

    Configures the ESP device to connect to the specified WiFi network with auto-connect and auto-reconnect features enabled.

  - ##### Parameters

    - `ssid` — the SSID of the WiFi network (default is `shs::settings::WIFI_SSID`).
    - `pass` — the password for the WiFi network (default is `shs::settings::WIFI_PASSWORD`).

- ##### `bool disableWiFi()`

  ```cpp
  static bool disableWiFi();
  ```

  - ##### Description

    Disables the WiFi functionality on the ESP device.

- ##### `bool enableWiFi()`

  ```cpp
  static bool enableWiFi();
  ```

  - ##### Description

    Enables the WiFi functionality on the ESP device.

- ##### `bool WiFiConnected()`

  ```cpp
  static bool WiFiConnected();
  ```

  - ##### Description

    Checks if the ESP device is currently connected to a WiFi network.

- ##### `bool setMac(mac)`

  ```cpp
  static bool setMac(uint8_t* mac);
  ```

  - ##### Description

    Sets the MAC address for the ESP device.

  - ##### Parameters

    - `mac` — pointer to the MAC address to set.

- ##### `shs::t::shs_IP_t localIP()`

  ```cpp
  static shs::t::shs_IP_t localIP();
  ```

  - ##### Description

    Returns the local IP address assigned to the ESP device.

### Example Usage

```cpp
#include <shs_ControlWiFi.h>
#include <shs_debug.h>

void setup() 
{
    dinit(); 

    shs::ControlWiFi::setHostname("MyESPDevice");
    doutln(shs::ControlWiFi::connectWiFiWait(20000) ? F("Connected to WiFi") : F("Failed to connect to WiFi."));
}

void loop() 
{
    // Your code here
}
```

## Conclusion

The `shs::ControlWiFi` class simplifies WiFi management for ESP microcontrollers, making it easier to connect to networks and manage WiFi settings. It is an essential utility for developers working with ESP devices in IoT applications.
