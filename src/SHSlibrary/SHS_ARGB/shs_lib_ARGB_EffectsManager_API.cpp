#include "shs_lib_ARGB_EffectsManager_API.h"

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <shs_lib_APIids.h>
#include <shs_DTPpacket.h>
#include <shs_ByteCollector.h>
#include <shs_utils.h>

shs::argb::EffectsManager_API::EffectsManager_API(shs::argb::EffectsManager& effects_manager, shs::t::shs_ID_t id)
    : shs::API(id.setComponentID(shs::etoi(shs::lib::APIids::ARGB_EFFECTS_MANAGER_API))),
    m_effects_manager(effects_manager)
{}

shs::DTPpacket shs::argb::EffectsManager_API::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (static_cast<Commands>(it.read()))
    {
        case Commands::RESET_EFFECTS: m_effects_manager.resetEffects(); break;
        case Commands::SET_RANDOM_MATRIX:
            {
                uint8_t min_color{};
                uint8_t max_color{};
                RandomMatrix::Direction direction{};
                shs::t::shs_time_t dt{};
                shs::t::shs_fixed_t min_line_length_ratio{};
                shs::t::shs_fixed_t max_line_length_ratio{};

                it.get(min_color, 1);
                it.get(max_color, 1);
                it.get(direction, 1);
                it.get(dt);
                it.get(min_line_length_ratio);
                it.get(max_line_length_ratio);

                m_effects_manager.setRandomMatrix(min_color, max_color, direction, dt, min_line_length_ratio, max_line_length_ratio);
            }
            break;
        default:
            break;
    }

    return shs::DTPpacket();
}

#endif // SHS_LIB_ARGB_NO_FASTLED
