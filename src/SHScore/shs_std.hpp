#pragma once


namespace std
{
    template <class T>
    T &&move(T &obj) { return static_cast<T &&>(obj) noexcept; }

    template <class Container>
    [[nodiscard]] constexpr auto begin(Container &Cont) noexcept(noexcept(Cont.begin()))
        -> decltype(Cont.begin())
    {
        return Cont.begin();
    }

    template <class Container>
    [[nodiscard]] constexpr auto begin(const Container &Cont) noexcept(noexcept(Cont.begin())) /* strengthened */
        -> decltype(Cont.begin())
    {
        return Cont.begin();
    }

    template <class Container>
    [[nodiscard]] constexpr auto end(Container &Cont) noexcept(noexcept(Cont.end())) /* strengthened */
        -> decltype(Cont.end())
    {
        return Cont.end();
    }

    template <class Container>
    [[nodiscard]] constexpr auto end(const Container &Cont) noexcept(noexcept(Cont.end())) /* strengthened */
        -> decltype(Cont.end())
    {
        return Cont.end();
    }
}
