# shs_debug.h

## General Description

This file contains a set of macros designed to facilitate the output of debugging information in applications using the SHS framework. These macros provide a convenient way to print messages to the console or serial output, making it easier to track the flow of execution and diagnose issues during development.

## Versions

- **v1.1.0** — created.
- **v2.0.0** — added a space in `dout()`, changed the debug flag.

## Macros

### Debug Initialization

- `#define dinit()` — initializes the debug output. This macro is mandatory for Arduino to start the Serial communication at a baud rate of 115200. For other platforms, this macro does nothing.

### Debug Output

- `#define dout(value)` — outputs a value to the debug console, followed by a space. For Arduino, it uses `Serial.print()`, while for other platforms, it uses `std::cout`.

- `#define doutln(value)` — outputs a value to the debug console, followed by a newline. For Arduino, it uses `Serial.println()`, while for other platforms, it uses `std::cout`.

- `#define dsep()` — outputs a separator line to the debug console for better readability.

## Example Usage

### C++ standard

```cpp
#include <shs_debug.h>

int main() 
{
    doutln("Debugging started");  // Print a debug message

    auto some_value = 42;
    dout("Current value: ");      // Print a message without a newline
    doutln(some_value);           // Print the value followed by a newline
    dsep();                       // Print a separator line

    return 0;
}
```

### Arduino

```cpp
#include <shs_debug.h>

void setup() 
{
    dinit();                      // Initialize debug output for Arduino
    doutln("Debugging started");  // Print a debug message
}

void loop() 
{
    dout("Current value: ");      // Print a message without a newline
    doutln(millis());             // Print the value followed by a newline
    dsep();                       // Print a separator line
    
    delay(1000);
}
```

## Conclusion

The `shs_debug.h` file provides essential macros for debugging output, making it easier for developers to track and diagnose issues in their applications. By using these macros, developers can streamline their debugging process and improve code readability.
