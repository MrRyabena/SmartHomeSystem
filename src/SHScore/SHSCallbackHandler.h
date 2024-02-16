#pragma once
#include "SHSvector.h"

namespace shs
{
    template <typename T>
    class CallbackHandler;
};

template <typename T>
class shs::CallbackHandler
{
public:
    explicit CallbackHandler() {}
    
    


private:
    shs::vector<T> m_ptrs;
};
