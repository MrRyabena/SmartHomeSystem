#pragma once

/*
    Last update: v1.0.0
    Versions:
        v0.2.0 — created.
        v1.0.0 — release.
*/

/*
    The "handler" class controls the load on the module itself.
    The "virtual" class implements the interface on the remote device.
*/

#include <memory>

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_APIids.h"
#include "shs_API.h"
#include "shs_Load.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_DTPpacket.h"

namespace shs
{
    class Load_API;
}


class shs::Load_API : public shs::API
{
public:
    enum Commands : uint8_t
    {
        ON8,
        ON16,
        OFF,
        GET_VALUE, VALUE
    };

    Load_API(shs::Load& load, shs::t::shs_ID_t ID) noexcept : API(ID.setComponentID(shs::constants::APIids::Load)), m_load(load) {}
    ~Load_API() = default;

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            [[likely]] case ON8: m_load.on(it.read()); break;
            case ON16: { uint16_t value{}; it.get(value, 2); m_load.on(value); } break;
            case OFF: m_load.off(); break;
            case GET_VALUE:
                {
                    shs::ByteCollector<> bc(3);
                    bc.push_back(VALUE, 1);
                    bc.push_back(m_load.getValue(), 2);

                    return shs::DTPpacket(std::move(bc));
                }
            default: break;
        }

        return shs::DTPpacket();
    }


private:
    shs::Load& m_load;
};
