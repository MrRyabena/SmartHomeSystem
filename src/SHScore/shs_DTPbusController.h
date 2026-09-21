#pragma once

#include "shs_settings_private.h"


#ifndef SHS_SF_AVR


#include <memory>

#include "shs_DTPbus.h"
#include "shs_DTPbusGeneralController.h"
#include "shs_Process.h"
#include "shs_ProgramTimer.h"
#include "shs_types.h"

namespace shs
{
    class DTPbusController;
}


/**
 * @brief A controller for managing a single DTP bus with a specific policy.
 * @note If the policy is set to UNKNOWN_POLICY, the bus policy will be used.
 * Otherwise, this policy will be more important and used for controlling the bus.
 */
class shs::DTPbusController : public shs::DTPbusGeneralController, public shs::Process
{
public:

    /**
     * @brief Creates a new DTP bus controller.
     * @param bus Weak pointer to the bus instance to control.
     * @param policy Policy to use for handling connection issues.
     * If it is set to UNKNOWN_POLICY, the bus policy will be used.
     * Otherwise, this policy will be more important and used for controlling the bus.
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

    /**
     * @brief Checks the status of the controlled DTP bus and return false
     * if the controller has no bus to control and can be removed.
     * @return True if the controller is still active, false if it has no bus to control.
     */
    bool isActive() const noexcept { return !m_bus.expired(); }

    /**
     * @brief Sets the bus policy. This policy will more important that the bus policy
     * and will be used for controlling the bus.
     * @param policy The new policy to set.
     */
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
