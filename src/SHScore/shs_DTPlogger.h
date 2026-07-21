#pragma once


#include "shs_settings_private.h"
#include "shs_DTPbus.h"
#include "shs_ByteCollector.h"
#include "shs_DTPpacket.h"

#include <memory>


namespace shs
{
    class DTPlogger;
    inline DTPlogger dtplog() { return {}; }
}


class shs::DTPlogger
{
public:
    static void setOutputBus(std::unique_ptr<shs::DTPbus> bus) { m_out = std::move(bus); }

    template <typename T>
    DTPlogger& operator<<([[maybe_unused]] const T& value)
    {
    #if defined(SHS_SF_DTP_LOGGER_ENABLED)
        shs::ByteCollector buf;
        buf.push_back(value);
        m_out->sendRAW(value);
    #endif

        return *this;
    }


private:
    static std::unique_ptr<shs::DTPbus> m_out;

};
