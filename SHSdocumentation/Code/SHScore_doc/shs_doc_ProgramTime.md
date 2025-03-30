# shs_ProgramTime.h

## General Description

This file contains the definition of the `shs::ProgramTime` class, which is used to track elapsed time since its creation. The class provides access to the runtime of the program or specific parts of it. It is cross-platform and supports both PC and microcontroller environments.

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — function names have been changed, optimized, fixed bugs, tested.

---

## Class `shs::ProgramTime`

### Description

`shs::ProgramTime` is a class that measures elapsed time since its instantiation. It provides methods to retrieve the elapsed time in microseconds, milliseconds, and seconds. The class is designed to work seamlessly on both Arduino platforms and standard PC environments. It is convenient to create timers based on this class.

### Members

- `size_t m_started` — The starting time of the program or process, stored as a timestamp.

---

### Constructors

- ##### `ProgramTime()`

  ```cpp
  ProgramTime();
  ```

  - ##### Description

    Initializes a new instance of the `ProgramTime` class and records the current time.

---

### Copy and Move Constructors

- ##### `ProgramTime(const ProgramTime& other)`

  ```cpp
  ProgramTime(const ProgramTime& other);
  ```

  - ##### Description

    Copy constructor that initializes a new instance with the starting time of another `ProgramTime` instance.

- ##### `ProgramTime(ProgramTime&& other)`

  ```cpp
  ProgramTime(ProgramTime&& other);
  ```

  - ##### Description

    Move constructor that transfers the starting time from another `ProgramTime` instance.

---

### Assignment Operators

- ##### `operator=(const ProgramTime& other)`

  ```cpp
  ProgramTime& operator=(const ProgramTime& other);
  ```

  - ##### Description

    Copy assignment operator that assigns the starting time from another `ProgramTime` instance.

- ##### `operator=(ProgramTime&& other)`

  ```cpp
  ProgramTime& operator=(ProgramTime&& other);
  ```

  - ##### Description

    Move assignment operator that transfers the starting time from another `ProgramTime` instance.

---

### Methods

- ##### `void reset()`

  ```cpp
  void reset();
  ```

  - ##### Description

    Resets the starting time to the current time.

---

- ##### `size_t microseconds() const`

  ```cpp
  size_t microseconds() const;
  ```

  - ##### Description

    Retrieves the elapsed time in microseconds since the instance was created.

  - ##### Returns

    The elapsed time in microseconds.

---

- ##### `size_t milliseconds() const`

  ```cpp
  size_t milliseconds() const;
  ```

  - ##### Description

    Retrieves the elapsed time in milliseconds since the instance was created.

  - ##### Returns

    The elapsed time in milliseconds.

---

- ##### `size_t seconds() const`

  ```cpp
  size_t seconds() const;
  ```

  - ##### Description

    Retrieves the elapsed time in seconds since the instance was created.

  - ##### Returns

    The elapsed time in seconds.

---

### Static Functions

- ##### `static size_t s_microseconds()`

  ```cpp
  static size_t s_microseconds();
  ```

  - ##### Description

    Retrieves the current time in microseconds since the system started.

  - ##### Returns

    The current time in microseconds.

---

- ##### `static size_t s_milliseconds()`

  ```cpp
  static size_t s_milliseconds();
  ```

  - ##### Description

    Retrieves the current time in milliseconds since the system started.

  - ##### Returns

    The current time in milliseconds.

---

- ##### `static size_t s_seconds()`

  ```cpp
  static size_t s_seconds();
  ```

  - ##### Description

    Retrieves the current time in seconds since the system started.

  - ##### Returns

    The current time in seconds.

---

### Example Usage

```cpp
shs::ProgramTime timer;  // Create a ProgramTime object

while (true)
{
    if (timer.milliseconds >= 1000) 
    {
        // do somthing

        timer.reset();
    }
}

```

---

## Conclusion

The `shs::ProgramTime` class is a vital component of the Smart Home System, providing a robust mechanism for tracking elapsed time. Its methods and constructors facilitate easy manipulation and retrieval of time values, ensuring efficient operation within the system.
