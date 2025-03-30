
# shs_Timer.h

## General Description

This file contains the definition of the `shs::Timer` class, which provides a timer functionality for managing periodic tasks within the Smart Home System. The class is designed to work with a specified process, allowing it to trigger actions at defined intervals.

## Versions

- **v2.0.0** — created.

---

## Class `shs::Timer`

### Description

`shs::Timer` is a class that inherits from `shs::Process` and manages a timer that can trigger a specified process at regular intervals. The timer can be configured with different resolutions (microseconds, milliseconds, or seconds) and allows for easy management of periodic tasks.

### Members

- `decltype(shs::timer_resolution::microseconds) m_res_func` — Function to retrieve the current time based on the specified resolution.
- `size_t m_T` — The period of the timer in the specified resolution.
- `size_t m_tmr` — The last recorded time when the timer was triggered.
- `shs::Process* m_process` — Pointer to the process that will be triggered by the timer.

---

### Constructors

- ##### `Timer(T, process, resolution)`

  ```cpp
  Timer(const size_t T = 0, shs::Process* process = nullptr,
        decltype(shs::timer_resolution::milliseconds) resolution = shs::timer_resolution::milliseconds);
  ```

  - ##### Description

    Initializes a `Timer` instance with a specified period, process to trigger, and resolution.

  - ##### Parameters

    - `T` — The period of the timer in the specified resolution (default is 0).
    - `process` — Pointer to the process that will be triggered by the timer (default is `nullptr`).
    - `resolution` — The resolution function to use for timing (default is milliseconds).

---

### Destructor

- ##### `~Timer()`

  ```cpp
  ~Timer() = default;
  ```

  - ##### Description

    Destructor for the `Timer` class.

---

### Methods

- ##### `void start() override`

  ```cpp
  void start() override;
  ```

  - ##### Description

    Starts the timer and the associated process if it is defined.

---

- ##### `void tick() override`

  ```cpp
  void tick() override;
  ```

  - ##### Description

    Checks if the timer period has elapsed and triggers the associated process if it has.

---

- ##### `void stop() override`

  ```cpp
  void stop() override;
  ```

  - ##### Description

    Stops the timer and the associated process if it is defined.

---

- ##### `void reset()`

  ```cpp
  void reset();
  ```

  - ##### Description

    Resets the timer to the current time.

---

- ##### `void setPeriod(T)`

  ```cpp
  void setPeriod(const size_t T);
  ```

  - ##### Description

    Sets a new period for the timer.

  - ##### Parameters

    - `T` — The new period of the timer in the specified resolution.

---

## Conclusion

The `shs::Timer` class provides a flexible and efficient way to manage periodic tasks within the Smart Home System. By allowing the user to specify the timing resolution and the process to trigger, it facilitates the implementation of time-sensitive functionalities in various applications.
