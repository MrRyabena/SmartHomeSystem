#pragma once

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>

#include "shs_lib_GRGB_EffectsManager.h"


namespace shs
{
    class GRGB_EffectsManager_API;
}


class shs::GRGB_EffectsManager_API : public shs::API
{
public:
    enum class Commands : uint8_t
    {
        NO_COMMAND,
        SET_COLOR_WHEEL,
        SET_BREATHING,
        RESET_COLOR_WHEEL,
        RESET_BREATHING
    }

    GRGB_EffectsManager_API(shs::GRGB_EffectsManager& em, shs::t::shs_ID_t ID)
        API(ID), m_em(em)
    {}

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it)
    {
        it.setPosition(shs::DTPpacket.get_DataBeg(it));

        switch (static_cast<Commands>(it.read()))
        {
            case Commands::SET_COLOR_WHEEL:
            {
                m_em.setColorWheel()
            }
        }

    }

protected:
    shs::GRGB_EffectsManager& m_em;
};
