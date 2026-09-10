#pragma once

#include "shs_settings_private.h"


#ifndef SHS_SF_AVR


#include <memory>

#include "shs_DTPbus.h"
#include "shs_DTPbusStatus.h"
#include "shs_DTPbusGeneralController.h"
#include "shs_Process.h"
#include "shs_ProgramTimer.h"
#include "shs_types.h"

namespace shs
{
    class DTPbusController;
}



class shs::DTPbusController : public shs::DTPbusGeneralController, public shs::Process
{
public:

    /**
     * @brief Creates a new DTP bus controller.
     * @param bus Weak pointer to the bus instance to control.
     * @param policy Policy to use for handling connection issues.
     * @param offline_timeout Timeout for considering a bus offline.
     * @param request_timeout Timeout for waiting for a response from the bus.
     * @param unused_timeout Timeout for considering a bus unused.
     */
    explicit DTPbusController(std::weak_ptr<shs::DTPbus> bus,
        shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT,
        shs::DTPbusPolicy policy = shs::DTPbusPolicy::UNKNOWN_POLICY
    );

    bool isActive() const noexcept { return !m_bus.expired(); }

    void setPolicy(shs::DTPbusPolicy policy) noexcept { m_policy = policy; }

    shs::DTPbusPolicy getPolicy() const noexcept { return m_getPolicy(m_bus.lock(), m_policy); }

    void start() override;
    void tick() override;
    void stop() override {}

protected:
    std::weak_ptr<shs::DTPbus> m_bus;
    shs::DTPbusPolicy m_policy;
};


#endif  // #ifndef SHS_SF_AVR
