#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/

#include "shs_settings_private.h"

#ifndef SHS_SF_AVR

#include <vector>
#include <algorithm>
#include <initializer_list>
#include <functional>

#include "shs_algorithm.h"

namespace shs
{
    template <typename BufT, typename Compare>
    class SortedBuf;
}


/**
 * @brief Ordered std::vector wrapper with sorted insertion, lookup, and removal helpers.
 * @tparam BufT Stored value type.
 * @tparam Compare Comparator type used for ordering.
 */
template <typename BufT, typename Compare = std::less<BufT>>
class shs::SortedBuf
{
public:
    /**
     * @brief Creates an empty sorted buffer.
        * @param compare Comparator instance used for ordering.
     */
    SortedBuf(Compare compare = Compare()) : m_compare(compare) {}

    /**
     * @brief Creates a sorted buffer from an initializer list.
        * @param list Initial values to store.
     */
    explicit SortedBuf(std::initializer_list<BufT> list) : m_compare(Compare()), m_srtdbuf(list) { std::sort(std::begin(m_srtdbuf), std::end(m_srtdbuf)); }

    /**
     * @brief Creates a sorted buffer from an initializer list using a custom comparator.
        * @param compare Comparator instance used for ordering.
        * @param list Initial values to store.
     */
    explicit SortedBuf(Compare compare, std::initializer_list<BufT> list) : m_compare(compare), m_srtdbuf(list) { std::sort(std::begin(m_srtdbuf), std::end(m_srtdbuf)); }

    /**
     * @brief Destroys the sorted buffer.
     */
    ~SortedBuf() = default;

    /**
     * @brief Inserts an element while preserving ordering.
        * @tparam T Input value type.
        * @param value Value to insert.
        * @return Iterator pointing to the inserted or matching element.
     */
    template <typename T>
    auto attach(T&& value) { return shs::insert_sorted(m_srtdbuf, std::forward<T>(value), m_compare); };


    /**
     * @brief Removes an element from the buffer.
        * @tparam T Input value type.
        * @param value Value to remove.
     */
    template <typename T>
    void detach(const T& value) { shs::remove_sorted(m_srtdbuf, value, m_compare); };

    /**
     * @brief Searches for a matching element.
        * @tparam T Search key type.
        * @param value Value or key to find.
        * @return Iterator to the found element or end iterator.
     */
    template <typename T>
    [[nodiscard]] auto get(const T& value) const { return shs::binary_search(begin(), end(), value, m_compare); }


    /**
     * @brief Returns an iterator to the beginning.
        * @return Const iterator to first element.
     */
    auto begin() const { return m_srtdbuf.begin(); }

    /**
     * @brief Returns an iterator to the end.
        * @return Const iterator past the last element.
     */
    auto end() const { return m_srtdbuf.end(); }

    /**
     * @brief Returns the number of stored elements.
        * @return Number of elements in the buffer.
     */
    auto size() const { return m_srtdbuf.size(); }

    /**
     * @brief Returns the last stored element.
        * @return Const reference-like value returned by std::vector::back().
     */
    auto back() const { return m_srtdbuf.back(); }

    /**
     * @brief Returns a reverse iterator to the last element.
        * @return Reverse iterator to the first reverse element.
     */
    auto rbegin() const { return m_srtdbuf.rbegin(); }

    /**
     * @brief Returns a reverse iterator to one before the first element.
        * @return Reverse iterator past the last reverse element.
     */
    auto rend() const { return m_srtdbuf.rend(); }

    /**
     * @brief Reports whether the buffer is empty.
        * @return True when no elements are stored.
     */
    auto empty() const { return m_srtdbuf.empty(); }

    /**
     * @brief Shrinks the buffer capacity to fit its size.
     */
    void shrink_to_fit() { m_srtdbuf.shrink_to_fit(); }

    /**
     * @brief Reserves storage for the current buffer implementation.
     */
    void reserve() { m_srtdbuf.reserve(); }

protected:
    /**
     * @brief Backing storage for sorted elements.
     */
    std::vector<BufT> m_srtdbuf;

    /**
     * @brief Comparator used for ordering.
     */
    Compare m_compare;
};

#endif    // #ifndef SHS_SF_AVR
