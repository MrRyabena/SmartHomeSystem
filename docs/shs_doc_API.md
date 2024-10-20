# shs_API.h

## General Description

This file contains the definition of the **abstract** class `shs::API`, which serves as a foundation for creating API handlers. If you want to create your own API class for something, you must inherit from `shs::API`.

## Versions
>
> - **v0.1.0** — created.
> - **v1.0.0** — release.
> - **v2.0.0** — changed types, using `shs::ID`, added virtual destructor.
>
## Class `shs::API`

### Description

`shs::API` is an abstract class that defines an interface for API handling. Classes that inherit from `shs::API` must implement the `handle` method.

### Constructor

```cpp
explicit API(const shs::t::shs_ID_t id);
```

- **Parameters**:
  - `id`: The API identifier of type `shs::t::shs_ID_t`.

### Virtual Destructor

```cpp
virtual ~API() = default;
```

### Methods

#### `virtual void handle(shs::ByteCollectorReadIterator<>& it) = 0;`

- **Description**: A pure virtual method that must be implemented in derived classes. This method processes data provided by the `ByteCollectorReadIterator`.

### Comparison Operators

- **`bool operator<(const shs::API& other) const`**
- **`bool operator>(const shs::API& other) const`**
- **`bool operator==(const shs::API& other) const`**
- **`bool operator!=(const shs::API& other) const`**

### Class Members

- **`shs::t::shs_ID_t API_ID`**: The API identifier, initialized in the constructor.

## Example Usage

```cpp
class MyAPI : public shs::API {
public:
    MyAPI(const shs::t::shs_ID_t id) : API(id) {}

    void handle(shs::ByteCollectorReadIterator<>& it) override 
    {
        // Implementation of data processing
    }
};
```

## Conclusion

The `shs::API` class provides a foundation for creating API handlers, offering the necessary interface and functionality for working with data. By inheriting this class, you can create your own API handlers by implementing the `handle` method to process specific data.
