# shs_utils.h

## General Description

This file contains utility functions for the Smart Home System. It provides a template function for converting enumeration values to their underlying integral types, enhancing type safety and usability in the codebase.

## Versions

- **v2.0.0** — created.

---

## Utility Functions

### `etoi`

- **Template Function**: `etoi(EnumT value)`

  ```cpp
  template <typename EnumT>
  constexpr auto etoi(EnumT value);
  ```

  - ##### Description

    Converts an enumeration value to its underlying integral type. This function is useful for obtaining the integer representation of enum values, allowing for easier manipulation and comparison.

  - ##### Parameters

    - `value` — The enumeration value to convert.

  - ##### Returns

    The underlying integral type of the enumeration value.

  - ##### Example Usage

    ```cpp
    enum class Color { Red, Green, Blue };
    auto colorValue = shs::etoi(Color::Green); // colorValue will be of type int and equal to 1
    ```

---

## Conclusion

The `shs_utils.h` file provides essential utility functions that enhance the functionality and type safety of the Smart Home System. The `etoi` function simplifies the process of working with enumerations, making the code more readable and maintainable.