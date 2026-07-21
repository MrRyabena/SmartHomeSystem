#pragma once


#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_types.h>

#include "shs_lib_ARGB_EffectsManager.h"

namespace shs
{
    namespace argb
    {
        class EffectsManager_API;
    }
}


class shs::argb::EffectsManager_API : public shs::API
{
public:
    enum class Commands : uint8_t
    {
        NO_COMMAND = 0,
        RESET_EFFECTS = 1,
        SET_RANDOM_MATRIX = 2,
    };

    EffectsManager_API(shs::argb::EffectsManager& effects_manager, shs::t::shs_ID_t id);

    ~EffectsManager_API() override = default;

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    shs::argb::EffectsManager& m_effects_manager;
};
