#pragma once

namespace shs::avr_std_detail
{
    template <typename T>
    struct remove_reference
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&>
    {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;
}


namespace std
{
    template <typename T>
    constexpr shs::avr_std_detail::remove_reference_t<T>&& move(T&& value) noexcept
    {
        return static_cast<shs::avr_std_detail::remove_reference_t<T>&&>(value);
    }
}
