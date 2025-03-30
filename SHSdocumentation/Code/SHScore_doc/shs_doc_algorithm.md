# shs_algorithm.h Documentation

## Overview

The `shs_algorithm.h` file contains template functions that provide algorithms for manipulating containers, including binary search, insertion, and removal of elements. These functions are designed to work with various container types in C++ and utilize standard algorithms to enhance performance and usability.

## Functions

### 1. `quick_remove_at`

```cpp
template <class Class>
inline void quick_remove_at(Class& obj, const size_t ind);
```

#### Description

This function removes an element from a container at a specified index (`ind`) by replacing it with the last element in the container and then popping the last element. This approach is efficient as it avoids shifting elements, making it suitable for scenarios where the order of elements is not critical.

#### Parameters

- `Class& obj` — the container from which the element will be removed.
- `size_t ind` — the index of the element to be removed.

#### Example Usage

```cpp
#include <vector>
#include <shs_algorithm.h>

std::vector<int> numbers = {1, 2, 3, 4, 5};
quick_remove_at(numbers, 2);                 // Removes the element at index 2 (value 3)
```

### 2. `binary_search`

```cpp
template <class It, typename T, typename Compare = std::less<T>>
[[nodiscard]] inline It binary_search(It left, It right, const T& key, Compare comp = Compare());
```

#### Description

This function performs a binary search on a sorted range defined by iterators `left` and `right` to find the position of a specified key. If the key is found, it returns an iterator to the key; otherwise, it returns an iterator to the end of the range.

#### Parameters

- `It left` — the beginning iterator of the range.
- `It right` — the ending iterator of the range.
- `const T& key` — the value to search for.
- `Compare comp` — a comparison function (default is `std::less<T>`).

#### Example Usage

```cpp
#include <vector>
#include <shs_algorithm.h>

std::vector<int> sorted_numbers = {1, 2, 3, 4, 5};

auto it = binary_search(std::begin(sorted_numbers), std::end(sorted_numbers), 3);

if (it != std::end(sorted_numbers)) std::cout << "Found: " << *it << std::endl;
else std::cout << "Not found" << std::endl;
    
```

### 3. `insert_sorted`

```cpp
template <class Container, typename T, typename Compare = std::less<T>>
inline auto insert_sorted(Container& container, T&& value, Compare comp = Compare());
```

#### Description

This function inserts a value into a sorted container while maintaining the sorted order. It uses binary search to find the appropriate position for the new value.

#### Parameters

- `Container& container` — the container where the value will be inserted.
- `T&& value` — the value to be inserted.
- `Compare comp` — a comparison function (default is `std::less<T>`).

#### Example Usage

```cpp
#include <vector>
#include <shs_algorithm.h>

std::vector<int> sorted_numbers = {1, 3, 4, 5};
insert_sorted(sorted_numbers, 2);                // Inserts 2 while maintaining order
```

### 4. `remove_sorted`

```cpp
template <class Container, typename T, typename Compare = std::less<T>>
inline void remove_sorted(Container& container, const T& value, Compare comp = Compare());
```

#### Description

This function removes a specified value from a sorted container. It uses binary search to find the value and then erases it from the container while maintaining the sorted order.

#### Parameters

- `Container& container` — the container from which the value will be removed.
- `const T& value` — the value to be removed.
- `Compare comp` — a comparison function (default is `std::less<T>`).

#### Example Usage

```cpp
#include <vector>
#include <shs_algorithm.h>

std::vector<int> sorted_numbers = {1, 2, 3, 4, 5};
remove_sorted(sorted_numbers, 3);                   // Removes the value 3 from the container
```

## Conclusion

The functions provided in `shs_algorithm.h` are designed to facilitate common operations on containers, such as searching, inserting, and removing elements while maintaining order. These template functions can be used with various container types, making them versatile tools for C++ developers.
