#pragma once


#include <streambuf>
#include <fstream>
#include <ios>


namespace shs
{
    template <class, class>
    class Basic_AFStream;

    using AFStream = Basic_AFStream<char, std::char_traits<char>>;
}


template <class CharT, class Traits = std::char_traits<ChartT>>
class shs::Basic_AFStream : public basic_fstream
{
public:
     

protected:

};
