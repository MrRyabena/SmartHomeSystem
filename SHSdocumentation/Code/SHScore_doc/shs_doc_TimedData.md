# shs_TimedData.h

## General Description

This file contains the definition of the `shs::TimedData` class, which is a container for storing data with expiration time control. The class ensures that stored data remains valid only for a specified time period. When the expiration time is reached, the data is considered outdated and can be freed.

## Versions

- **v2.0.0** — created for use in sensor classes.

---

## Class `shs::TimedData`

### Description

`shs::TimedData` is a template class that manages data with an associated expiration time. It provides methods to update the data, check its validity, and free expired data. The template parameter `DataT` defines the type of stored data.

### Template Parameter

- `DataT` — The type of data to be stored in the container.

### Members

- `shs::ProgramTime m_timer` — Timer used to track the elapsed time since the data was last updated.
- `uint32_t m_expiration_time` — The expiration time in milliseconds.
- `DataT* m_data_ptr` — Pointer to the stored data.

---

### Constructors

- ##### `TimedData(expiration_time)`

  ```cpp
  TimedData(const uint32_t expiration_time);
  ```

  - ##### Description

    Initializes a `TimedData` instance with a specified expiration time.

  - ##### Parameters

    - `expiration_time` — The time period (in milliseconds) after which the data is considered expired.

---

### Destructor

- ##### `~TimedData()`

  ```cpp
  ~TimedData();
  ```

  - ##### Description

    Destructor for the `TimedData` class, which frees the allocated data.

---

### Methods

- ##### `void setExpiration(expiration_time)`

  ```cpp
  void setExpiration(const uint32_t expiration_time);
  ```

  - ##### Description

    Sets a new expiration time for the stored data.

  - ##### Parameters

    - `expiration_time` — The new expiration time in milliseconds.

---

- ##### `auto getExpiration() const`

  ```cpp
  auto getExpiration() const;
  ```

  - ##### Description

    Retrieves the current expiration time.

  - ##### Returns

    The expiration time in milliseconds.

---

- ##### `auto getRemainingExpiration() const`

  ```cpp
  auto getRemainingExpiration() const;
  ```

  - ##### Description

    Calculates the remaining time before the data expires.

  - ##### Returns

    The remaining expiration time in milliseconds.

---

- ##### `void update(data)`

  ```cpp
  void update(const DataT& data);
  void update(DataT&& data);
  ```

  - ##### Description

    Updates the stored data with a new value and resets the timer.

  - ##### Parameters

    - `data` — The new data to store (can be passed by value or moved).

---

- ##### `[[nodiscard]] const DataT& getData() const`

  ```cpp
  [[nodiscard]] const DataT& getData() const;
  ```

  - ##### Description

    Retrieves a reference to the stored data.

  - ##### Returns

    A constant reference to the stored data.

---

- ##### `void reset()`

  ```cpp
  void reset();
  ```

  - ##### Description

    Resets the timer for the stored data.

---

- ##### `bool hasData() const`

  ```cpp
  bool hasData() const;
  ```

  - ##### Description

    Checks if there is valid data stored.

  - ##### Returns

    `true` if data is present; otherwise, `false`.

---

- ##### `bool isExpired() const`

  ```cpp
  bool isExpired() const;
  ```

  - ##### Description

    Checks if the stored data has expired.

  - ##### Returns

    `true` if the data is expired; otherwise, `false`.

---

- ##### `bool freeExpired()`

  ```cpp
  bool freeExpired();
  ```

  - ##### Description

    Frees the stored data if it has expired.

  - ##### Returns

    `true` if the data was freed; otherwise, `false`.

---

### Type Conversion Operators

- ##### `operator bool() const`

  - Converts the `TimedData` instance to a boolean indicating whether the data is valid (not expired).

- ##### `DataT& operator*()`

  - Returns a reference to the stored data.

- ##### `DataT* operator&()`

  - Returns a pointer to the stored data.

- ##### `DataT* operator->()`

  - Returns a pointer to the stored data.

- ##### `const DataT* operator->() const`

  - Returns a constant pointer to the stored data.

---

### Example Usage

```cpp
shs::TimedData<int> timedData(5000);  // Create a TimedData instance with a 5-second expiration
timedData.update(42);                 // Update the data
if (!timedData.isExpired()) 
{
    int value = timedData.getData();  // Retrieve the stored data
}
```

---

## Conclusion

The `shs::TimedData` class provides a flexible way to manage data with expiration control, making it suitable for use in sensor classes and other applications where data validity is time-sensitive. Its methods allow for easy data management and expiration handling.
