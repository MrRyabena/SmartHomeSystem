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

- `static bool setHostname(const char* hostname)` — sets the hostname for the ESP device.

- `static void connectWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD)` — initiates a connection to the specified WiFi network using the provided SSID and password.

- `static bool connectWiFiWait(const size_t time = 20000, const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD)` — connects to the specified WiFi network and waits for the connection to be established within the given time limit.

- `static void configureWiFi(const char* ssid = shs::settings::WIFI_SSID, const char* pass = shs::settings::WIFI_PASSWORD)` — configures the ESP device to connect to the specified WiFi network with auto-connect and auto-reconnect features enabled.

- `static bool disableWiFi()` — disables the WiFi functionality on the ESP device.

- `static bool enableWiFi()` — enables the WiFi functionality on the ESP device.

- `static bool WiFiConnected()` — checks if the ESP device is currently connected to a WiFi network.

- `static bool setMac(uint8_t* mac)` — sets the MAC address for the ESP device.

- `static shs::t::shs_IP_t localIP()` — returns the local IP address assigned to the ESP device.

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
