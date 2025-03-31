#include "shs_lib_MHZ19.h"

uint8_t shs::MHZ19::getStatus()
{

    switch (m_mhz19.getStatus())
    {
        case -1: return static_cast<uint8_t>(Status::NO_RESPONSE);        break;
        case 0:  return static_cast<uint8_t>(Status::UNDEFINED);          break;
        case 64: return static_cast<uint8_t>(Status::HIGH_ACCURACY);      break;
        case 32: return static_cast<uint8_t>(Status::INCREASED_ACCURACY); break;
        case 16: return static_cast<uint8_t>(Status::MEDIUM_ACCURACY);    break;
        case 8:  return static_cast<uint8_t>(Status::REDUCED_ACCURACY);   break;
        case 4:  return static_cast<uint8_t>(Status::LOW_ACCURACY);       break;
        default: return static_cast<uint8_t>(Status::UNDEFINED);          break;
    }

    return static_cast<uint8_t>(Status::UNDEFINED);
}
