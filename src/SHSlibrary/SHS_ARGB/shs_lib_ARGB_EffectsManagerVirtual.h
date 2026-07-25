#pragma once

#include <shs_DTP.h>


#include "shs_lib_ARGB_EffectsManager_API.h"
#include "shs_lib_ARGB_RandomMatrix.h"

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
    EffectsManagerVirtual(shs::t::shs_ID_t this_id, shs::t::shs_ID_t remote_id, shs::DTP& dtp);
    ~EffectsManagerVirtual() = default;

    void setRandomMatrix(uint8_t min_color = 0, uint8_t max_color = 255,
        RandomMatrix::Direction direction = RandomMatrix::Direction::BEGIN,
        shs::t::shs_time_t dt = 50,
        shs::t::shs_float_t min_line_length_ratio = 0.05,
        shs::t::shs_float_t max_line_length_ratio = 0.5);

    void resetEffects();

protected:
    shs::DTP& m_dtp;
    shs::t::shs_ID_t m_this_id;
    shs::t::shs_ID_t m_remote_id;
};
