# shs_SortedBuf.h

## General Description

This file contains the definition of the `shs::SortedBuf` class, which is a container that maintains an ordered `std::vector`. The class utilizes algorithms from `shs_algorithm.h` to ensure that the elements are always sorted upon insertion and allows for efficient searching, insertion, and removal of elements.

## Versions

- **v2.0.0** — created.

---

## Class `shs::SortedBuf`

### Description

`shs::SortedBuf` is a template class that provides a sorted buffer based on `std::vector`. It automatically sorts the elements when they are added, ensuring that the container remains in a sorted state. The class supports various operations such as insertion, removal, and searching using binary search.

### Template Parameters

- `BufT` — The type of elements stored in the buffer.
- `Compare` — The comparison function used to maintain order (default is `std::less<BufT>`).

### Members

- `std::vector<BufT> m_srtdbuf` — The underlying vector that stores the sorted elements.
- `Compare m_compare` — The comparison function used for sorting and searching.

---

### Constructors

- ##### `SortedBuf(compare)`

  ```cpp
  SortedBuf(Compare compare = Compare());
  ```

  - ##### Description

    Initializes a `SortedBuf` instance with a specified comparison function.

  - ##### Parameters

    - `compare` — The comparison function used for sorting (default is `Compare()`).

---

- ##### `SortedBuf(list)`

  ```cpp
  explicit SortedBuf(std::initializer_list<BufT> list);
  ```

  - ##### Description

    Initializes a `SortedBuf` instance with an initializer list and sorts the elements.

  - ##### Parameters

    - `list` — An initializer list of elements to be added to the buffer.

---

- ##### `SortedBuf(compare, list)`

  ```cpp
  explicit SortedBuf(Compare compare, std::initializer_list<BufT> list);
  ```

  - ##### Description

    Initializes a `SortedBuf` instance with a specified comparison function and an initializer list, sorting the elements.

  - ##### Parameters

    - `compare` — The comparison function used for sorting.
    - `list` — An initializer list of elements to be added to the buffer.

---

### Methods

- ##### `auto attach(value)`

  ```cpp
  template <typename T>
  auto attach(T&& value);
  ```

  - ##### Description

    Inserts a value into the sorted buffer, maintaining the sorted order.

  - ##### Parameters

    - `value` — The value to be inserted.

  - ##### Returns

    An iterator to the newly inserted element.

---

- ##### `void detach(value)`

  ```cpp
  template <typename T>
  void detach(const T& value);
  ```

  - ##### Description

    Removes a specified value from the sorted buffer.

  - ##### Parameters

    - `value` — The value to be removed.

---

- ##### `auto get(value) const`

  ```cpp
  template <typename T>
  [[nodiscard]] auto get(const T& value) const;
  ```

  - ##### Description

    Searches for a specified value in the sorted buffer using binary search.

  - ##### Parameters

    - `value` — The value to search for.

  - ##### Returns

    An iterator to the found element, or the end iterator if not found.

---

- ##### `auto begin() const`

  ```cpp
  auto begin() const;
  ```

  - ##### Description

    Returns an iterator to the beginning of the sorted buffer.

---

- ##### `auto end() const`

  ```cpp
  auto end() const;
  ```

  - ##### Description

    Returns an iterator to the end of the sorted buffer.

---

- ##### `auto size() const`

  ```cpp
  auto size() const;
  ```

  - ##### Description

    Returns the number of elements in the sorted buffer.

---

- ##### `auto back() const`

  ```cpp
  auto back() const;
  ```

  - ##### Description

    Returns a reference to the last element in the sorted buffer.

---

- ##### `auto rbegin() const`

  ```cpp
  auto rbegin() const;
  ```

  - ##### Description

    Returns a reverse iterator to the beginning of the sorted buffer.

---

- ##### `auto rend() const`

  ```cpp
  auto rend() const;
  ```

  - ##### Description

    Returns a reverse iterator to the end of the sorted buffer.

---

- ##### `auto empty() const`

  ```cpp
  auto empty() const;
  ```

  - ##### Description

    Checks if the sorted buffer is empty.

  - ##### Returns

    `true` if the buffer is empty; otherwise, `false`.

---

- ##### `void shrink_to_fit()`

  ```cpp
  void shrink_to_fit();
  ```

  - ##### Description

    Reduces the capacity of the sorted buffer to fit its size.

---

- ##### `void reserve()`

  ```cpp
  void reserve();
  ```

  - ##### Description

    Reserves space for the specified number of elements in the sorted buffer.

---

### Example Usage

```cpp
shs::SortedBuf<int> sortedBuffer;  // Create a SortedBuf instance for integers
sortedBuffer.attach(5);            // Insert value 5
sortedBuffer.attach(3);            // Insert value 3, buffer remains sorted
sortedBuffer.detach(5);            // Remove value 5
```

---

## Conclusion

The `shs::SortedBuf` class provides a convenient way to maintain a sorted collection of elements using `std::vector`. By leveraging algorithms from `shs_algorithm.h`, it ensures efficient insertion, removal, and searching of elements, making it a valuable tool for managing ordered data in applications.
