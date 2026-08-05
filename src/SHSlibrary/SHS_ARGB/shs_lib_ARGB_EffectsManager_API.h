#pragma once

#ifndef SHS_LIB_ARGB_NO_FASTLED

#include <shs_API.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_types.h>

#include "shs_lib_ARGB_EffectsManager.h"

#include "shs_lib_ARGB_EffectsManager_API_Commands.h"

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
    using Commands = shs::argb::EffectsManager_API_Commands;

    EffectsManager_API(shs::argb::EffectsManager& effects_manager, shs::t::shs_ID_t id);

    ~EffectsManager_API() override = default;

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    shs::argb::EffectsManager& m_effects_manager;
};

#endif // SHS_LIB_ARGB_NO_FASTLED
