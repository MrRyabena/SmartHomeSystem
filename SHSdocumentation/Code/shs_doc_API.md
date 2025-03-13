# shs_API.h

## General Description

This file contains the definition of the **abstract** class `shs::API`, which serves as a foundation for creating API handlers. If you want to create your own API class for something, you must inherit from `shs::API`.

## Versions

- **v0.1.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — changed types, using `shs::ID`, added virtual destructor.

## Class `shs::API`

### Description

`shs::API` is an abstract class that defines an interface for API handling. Classes that inherit from `shs::API` must implement the `handle` method.

### Constructor

```cpp
explicit API(const shs::t::shs_ID_t id);
```

- **Parameters**:
  - **id** — the API identifier of type `shs::t::shs_ID_t`.

### Destructor

```cpp
virtual ~API() = default;
```

### Methods

#### `virtual shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) = 0;`

#### Description

A pure virtual method that must be implemented in derived classes. This method processes data provided by the `ByteCollectorReadIterator` and returns a response to the request. If no response is required, it returns an empty `shs::DTPpacket`.

### Comparison Operators

- **`bool operator<(const shs::API& other) const`** — compares the API identifier with another API instance.
- **`bool operator>(const shs::API& other) const`** — compares the API identifier with another API instance.
- **`bool operator==(const shs::API& other) const`** — checks if two API instances are equal based on their identifiers.
- **`bool operator!=(const shs::API& other) const`** — checks if two API instances are not equal based on their identifiers.

### Class Members

- **shs::t::shs_ID_t API_ID** — the API identifier, initialized in the constructor.

## Example Usage

```cpp
class MyAPI : public shs::API 
{
public:
    MyAPI(const shs::t::shs_ID_t id) : API(id) {}

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override 
    {
        // Implementation of data processing
        return shs::DTPpacket();
    }
};
```

## Conclusion

The `shs::API` class provides a foundation for creating API handlers, offering the necessary interface and functionality for working with data. By inheriting this class, you can create your own API handlers by implementing the `handle` method to process specific data.
