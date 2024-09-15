#pragma once

#include <stddef.h>
#include <functional>

#include "shs_settings_private.h"

namespace shs
{
    template <class Class>
    inline void quick_remove_at(Class& obj, const size_t ind)
    {
        obj[ind] = std::move(obj.back());
        obj.pop_back();
    }

    template <class It, typename T, typename Compare = std::less<T>>
    [[nodiscard]] It binary_search(It left, It right, const T& key, Compare comp = Compare())
    {
        const auto end = right;
        while (left < right)
        {
            It m{ left + (right - left) / 2 };
            comp(*m, key) ? left = m + 1 : right = m;
        }

        if (left != end && !comp(key, *left)) return left;
        return end;

    }

    template <class Container, typename T, typename Compare = std::less<T>>
    auto insert_sorted(Container& container, T&& value, Compare comp = Compare())
    {
        auto left = std::begin(container);
        auto right = std::end(container);

        while (left < right)
        {
            auto m{ left + (right - left) / 2 };
            comp(*m, value) ? left = m + 1 : right = m;
        }
        
        return container.insert(left, std::forward<T>(value));
        // auto ins_it = std::inserter(container, left);
        // *ins_it = std::forward<T>(value);

    }

    template <class Container, typename T, typename Compare = std::less<T>>
    inline void remove_sorted(Container& container, const T& value, Compare comp = Compare())
    {
        auto left = std::begin(container);
        auto right = std::end(container);

        while (left < right)
        {
            auto m{ left + (right - left) / 2 };
            comp(*m, value) ? left = m + 1 : right = m;
        }

        container.erase(comp(*left, value) ? std::end(container) : left);
        container.shrink_to_fit();
    }

} // namespace shs
