#pragma once

#include "shs_AFStream.h"


namespace shs
{
    class 

    template <class, class>
    class Basic_AFStreamBuf;

    using AFStreamBuf = Basic_AFStreamBuf<char, std::char_traits<char>>;
}


template <class CharT, class Traits = std::char_traits<ChatT>>
class Basic_AFStreamBuf : public shs::Basic_AStreamBuf<CharT, Traits>
{
public:
    Basic_AFStreamBuf(File& file) : m_astream(file) {}


    typename Traits::int_type underflow() override
    {
        if (m_astream.available() == 0) return Traits::eof();
        auto c = m_astream.peek();
        return (c == -1) ? Traits::eof() : Traits::to_int_type(c);
    }


    typename Traits::int_type uflow() override
    {
        if (m_astream.available() == 0) return Traits::eof();
        auto c = m_astream.read();
        return (c == -1) ? Traits::eof() : Traits::to_int_type(c);
    }
};
