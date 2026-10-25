#include "shs_lib_ARGB_EffectsManagerVirtual.h"

#include <memory>

#include <shs_utils.h>

#include <shs_lib_APIids.h>

shs::argb::EffectsManagerVirtual::EffectsManagerVirtual(shs::t::shs_ID_t this_id, shs::t::shs_ID_t remote_id, shs::DTP& dtp)
    : m_dtp(dtp), m_this_id(this_id.setComponentID(shs::etoi(shs::lib::APIids::ARGB_EFFECTS_MANAGER_API))),
    m_remote_id(remote_id.setComponentID(shs::etoi(shs::lib::APIids::ARGB_EFFECTS_MANAGER_API)))

{}

void shs::argb::EffectsManagerVirtual::setRandomMatrix(uint8_t min_color, uint8_t max_color, shs::argb::RandomMatrix_Direction direction, shs::t::shs_time_t dt, shs::t::shs_float_t min_line_length_ratio, shs::t::shs_float_t max_line_length_ratio)
{
    shs::ByteCollector<> bc(11);
    bc.push_back(Commands::SET_RANDOM_MATRIX, 1);
    bc.push_back(min_color, 1);
    bc.push_back(max_color, 1);
    bc.push_back(direction, 1);
    bc.push_back(dt, 4);
    bc.push_back(min_line_length_ratio);
    bc.push_back(max_line_length_ratio);

    m_dtp.sendPacket(shs::DTPpacket(m_this_id, m_remote_id, std::move(bc)));
}

void shs::argb::EffectsManagerVirtual::setFire(const uint8_t start_hue, const uint8_t hue_gap,
    const uint8_t fire_step, const uint8_t min_bright, const uint8_t max_bright,
    const uint8_t min_sat, const uint8_t max_sat)
{
    shs::ByteCollector<> bc(8);
    bc.push_back(Commands::SET_FIRE, 1);
    bc.push_back(start_hue, 1);
    bc.push_back(hue_gap, 1);
    bc.push_back(fire_step, 1);
    bc.push_back(min_bright, 1);
    bc.push_back(max_bright, 1);
    bc.push_back(min_sat, 1);
    bc.push_back(max_sat, 1);

    m_dtp.sendPacket(shs::DTPpacket(m_this_id, m_remote_id, std::move(bc)));
}

void shs::argb::EffectsManagerVirtual::resetEffects()
{
    shs::ByteCollector<> bc(1);
    bc.push_back(Commands::RESET_EFFECTS, 1);

    m_dtp.sendPacket(shs::DTPpacket(m_this_id, m_remote_id, std::move(bc)));
}
