#pragma once

#include <stddef.h>

#include "shs_settings_private.h"

namespace shs
{
        template <class Class>
        void quick_remove_at(Class &obj, size_t ind)
        {
#ifdef SHS_SF_UNUSE_STL
                obj[ind] = obj.back();
#else
                obj[ind] = std::move(obj.back());
#endif
                obj.pop_back();
        }
};
