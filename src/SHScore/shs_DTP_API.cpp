#include "shs_DTP_API.h"


/**
 * @brief TODO!!
 * 
 * @param it 
 * @return shs::DTPpacket 
 */
shs::DTPpacket shs::DTP_APIhandler::handle(shs::ByteCollectorReadIterator<>& it)
{
    switch (shs::DTPpacket::get_DTPcode(it))
    {
        case shs::DTPpacket::INITIAL: break;
        case shs::DTPpacket::INITIAL_ANSWER: break;
        default: break;
    }

    return {};
}
