#pragma once

#include <shs_DTP.h>


#include "shs_lib_ARGB_EffectsManager_API_Commands.h"
#include "shs_lib_ARGB_RandomMatrix_Direction.h"

namespace shs
{
    namespace argb
    {
        class EffectsManagerVirtual;
    }
}


class shs::argb::EffectsManagerVirtual
{
public:
    using Commands = shs::argb::EffectsManager_API_Commands;

    EffectsManagerVirtual(shs::t::shs_ID_t this_id, shs::t::shs_ID_t remote_id, shs::DTP& dtp);
    ~EffectsManagerVirtual() = default;

    void setRandomMatrix(uint8_t min_color = 0, uint8_t max_color = 255,
        shs::argb::RandomMatrix_Direction direction = shs::argb::RandomMatrix_Direction::BEGIN,
        shs::t::shs_time_t dt = 50,
        shs::t::shs_float_t min_line_length_ratio = 0.05,
        shs::t::shs_float_t max_line_length_ratio = 0.5);

    void resetEffects();

protected:
    shs::DTP& m_dtp;
    shs::t::shs_ID_t m_this_id;
    shs::t::shs_ID_t m_remote_id;
};
