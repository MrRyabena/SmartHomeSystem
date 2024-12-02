#pragma once

#include <vector>
#include <functional>

#include "shs_algorithm.h"

namespace shs
{
    template <typename BufT, typename Compare>
    class SortedBuf;
}

template <typename BufT, typename Compare = std::less<BufT>>
class shs::SortedBuf
{
public:
    SortedBuf(Compare compare = Compare()) : m_compare(compare) {}
    ~SortedBuf() = default;

    template <typename T>
    auto attach(T&& value) { return shs::insert_sorted(m_srtdbuf, std::forward<T>(value), m_compare); };


    template <typename T>
    void detach(const T& value) { shs::remove_sorted(m_srtdbuf, value, m_compare); };

    template <typename T>
    [[nodiscard]] auto get(const T& value) const { return shs::binary_search(begin(), end(), value, m_compare); }


    auto begin() const { return m_srtdbuf.begin(); }
    auto end() const { return m_srtdbuf.end(); }
    auto size() const { return m_srtdbuf.size(); }
    auto back() const { return m_srtdbuf.back(); }
    auto rbegin() const { return m_srtdbuf.rbegin(); }

    void shrink_to_fit() { m_srtdbuf.shrink_to_fit(); }
    void reserve() { m_srtdbuf.reserve(); }

protected:
    std::vector<BufT> m_srtdbuf;
    Compare m_compare;
};
