#pragma once

#include "shs_settings_private.h"

#ifndef SHS_SF_AVR

#include <memory>

#include "shs_DTPbus.h"
#include "shs_Process.h"
#include "shs_ProgramTimer.h"
#include "shs_types.h"

namespace shs
{
    class DTPbusGeneralController;
}


/**
 * @brief A general controller for managing many DTP buses.
 * This class is responsible for monitoring the states of multiple DTP buses and
 * applying the appropriate policies based on their current state.
 *
 * This class can check bus timers, send connection requests and set the active state
 * of buses based on their policies and timeouts:
 *
 * TEMPORARY_IF_NO_ANSWERS: If no packets are received within the request timeout,
 * a connection request is sent. If still no packets are received within the offline
 * timeout, the bus is stopped and set to inactive.
 *
 * TEMPORARY_IF_DISCONNECTED: Similar to TEMPORARY_IF_NO_ANSWERS, but also considers
 * the case where the bus is disconnected.
 *
 * TEMPORARY_IF_UNUSED: If the bus is not used (no packets are received or sent) within the
 * unused timeout, the bus is stopped and set to inactive.
 *
 * @note This class is designed to be used as default controller for DTP busses. If
 * need the specific controller for a bus, needed to use the shs::DTPbusController class
 * or implement your own controller class that inherits from this one.
 */
class shs::DTPbusGeneralController
{
public:
    static constexpr auto DEFAULT_REQUEST_TIMEOUT = 30000;   // ms, 30 seconds
    static constexpr auto DEFAULT_OFFLINE_TIMEOUT = 180000;  // ms, 3 minutes (REQUEST_TIMEOUT * 6)
    static constexpr auto DEFAULT_UNUSED_TIMEOUT = 600000;   // ms, 10 minutes

    /**
     * @brief Creates a new DTP bus controller.
     * @param bus Weak pointer to the bus instance to control.
     * @param policy Policy to use for handling connection issues.
     * @param offline_timeout Timeout for considering a bus offline.
     * @param request_timeout Timeout for waiting for a response from the bus.
     * @param unused_timeout Timeout for considering a bus unused.
     */
    explicit DTPbusGeneralController(shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT
    );

    void setRequestTimeout(shs::t::shs_time_t timeout) noexcept { m_request_timer.setTimeout(timeout); }
    void setOfflineTimeout(shs::t::shs_time_t timeout) noexcept { m_offline_timeout = timeout; }
    void setUnusedTimeout(shs::t::shs_time_t timeout) noexcept { m_unused_timeout = timeout; }

    shs::t::shs_time_t getRequestTimeout() const noexcept { return m_request_timer.getTimeout(); }
    shs::t::shs_time_t getOfflineTimeout() const noexcept { return m_offline_timeout; }
    shs::t::shs_time_t getUnusedTimeout() const noexcept { return m_unused_timeout; }

    void controlBus(std::shared_ptr<shs::DTPbus> bus);

    /**
     * @brief Checks the status of a DTP bus and applies the appropriate policy.
     * @param bus Shared pointer to the bus instance to check.
     * @param policy Policy to use for handling connection issues.
     * @param offline_timeout Timeout for considering a bus offline.
     * @param request_timeout Timeout for waiting for a response from the bus.
     * @param unused_timeout Timeout for considering a bus unused.
     */
    static void s_controlBus(std::shared_ptr<shs::DTPbus> bus,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT,
        shs::DTPbusPolicy policy = shs::DTPbusPolicy::UNKNOWN_POLICY
    );

protected:
    shs::ProgramTimer m_request_timer;
    shs::t::shs_time_t m_offline_timeout;
    shs::t::shs_time_t m_unused_timeout;

    static shs::DTPbusPolicy m_getPolicy(std::shared_ptr<shs::DTPbus> bus, shs::DTPbusPolicy policy) noexcept;
};


#endif // #ifndef SHS_SF_AVR
