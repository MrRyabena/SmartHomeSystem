#pragma once


namespace std
{
    template <typename T>
    T&& move(const T& value) { return (T&&)value; }
}
