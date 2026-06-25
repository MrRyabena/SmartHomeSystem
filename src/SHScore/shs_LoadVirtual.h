#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — redesigned, debugged and tested.
*/

/*
  The "handler" class controls the load on the module itself.
  The "virtual" class implements the interface on the remote device.
*/


#include "shs_settings_private.h"

#ifndef SHS_SF_AVR

#ifdef SHS_SF_AVR
#include <shs_lib_AVR_STD_memory.h>
#else
#include <memory>
#endif 

#include "shs_Load.h"
#include "shs_API.h"
#include "shs_types.h"
#include "shs_DTP.h"
#include "shs_DTPpacket.h"
#include "shs_Load_API.h"
#include "shs_APIids.h"


namespace shs
{
    class LoadVirtual;
}


/**
 * @brief Virtual load implementation that proxies control to a remote device over DTP.
 */
class shs::LoadVirtual : public shs::Load, public shs::API
{
public:
    /**
     * @brief Creates a virtual load bound to a remote load identifier.
     * @param thisID Local API identifier for this virtual load.
     * @param virtualID Remote load identifier to control.
     * @param dtp DTP transport used to send commands.
     * @param l_type Load type to report for this virtual load.
     */
    LoadVirtual(const shs::t::shs_ID_t thisID, shs::t::shs_ID_t virtualID, shs::DTP& dtp, const Type l_type = shs::Load::Type::UNKNOWN)
        : Load(l_type), API(thisID), m_virtualID(virtualID.setComponentID(shs::constants::APIids::Load)), m_dtp(dtp)
    {}

    /**
     * @brief Destroys the virtual load.
     */
    ~LoadVirtual() = default;

    
    // -------------------- API --------------------
    /**
     * @brief Load command set reused from the concrete load API.
     */
    using Commands = shs::Load_API::Commands;

    /**
     * @brief Handles incoming DTP commands.
     */
    shs::DTPpacket handle([[maybe_unused]]shs::ByteCollectorReadIterator<>& it) override { return shs::DTPpacket(); }

    
    // -------------------- Load --------------------
    /**
     * @brief Initializes the virtual load interface.
     */
    void setup() override {}

    /**
     * @brief Sends an ON command to the remote load.
     */
    void on(const uint16_t value = UINT16_MAX) override;

    /**
     * @brief Sends an OFF command to the remote load.
     */
    void off() override;


protected:
    /**
     * @brief Identifier of the remote load endpoint.
     */
    shs::t::shs_ID_t m_virtualID;

    /**
     * @brief DTP transport used to send commands.
     */
    shs::DTP& m_dtp;
};

#endif  // SHS_SF_AVR
