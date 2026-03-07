#pragma once

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>

#include <shs_lib_APIids.h>
#include <shs_utils.h>

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
    };

    GRGB_EffectsManager_API(shs::GRGB_EffectsManager& em, shs::t::shs_ID_t ID)
        : API(ID.setComponentID(shs::etoi(shs::lib::APIids::GRGB_EFFECTS_MANAGER_API))), m_em(em)
    {}

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (static_cast<Commands>(it.read()))
        {
            case Commands::SET_COLOR_WHEEL:
                {
                    shs::t::shs_time_t dt{};
                    int16_t shift{};
                    it.get(dt, 4);
                    it.get(shift, 2);

                    m_em.setColorWheel(dt, shift);
                }
                break;
            case Commands::SET_BREATHING:
                {
                    shs::t::shs_time_t dt{};
                    int16_t increment{};
                    uint16_t start_brightness{};
                    uint8_t min_brightness{};
                    uint8_t max_brightness{};

                    it.get(dt, 4);
                    it.get(increment, 2);
                    it.get(start_brightness, 2);
                    it.get(min_brightness, 1);
                    it.get(max_brightness, 1);

                    m_em.setBreathing(dt, increment, start_brightness, min_brightness, max_brightness);
                }
                break;
            case Commands::RESET_COLOR_WHEEL:
            {
                m_em.resetColorWheel();
            }
            break;
            case Commands::RESET_BREATHING:
            {
                m_em.resetBreathing();
            }
            break;
        }

        return {};

    }

protected:
    shs::GRGB_EffectsManager& m_em;
};
