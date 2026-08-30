#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.1.0 — created.
    v2.3.0 — updated docs.
*/

#include "shs_ProgramTime.h"



namespace shs
{
    class ProgramTimer;
}


/**
 * @brief One-shot timeout helper built on top of shs::ProgramTime.
 */
class shs::ProgramTimer : public shs::ProgramTime
{
public:
    /**
     * @brief Timer resolution options.
     * @note Default resolution is milliseconds.
     */
    enum class Resolution : uint8_t { MICROSECONDS, MILLISECONDS, SECONDS };

    static constexpr auto MAX_TIMEOUT = std::numeric_limits<size_t>::max();

    /**
     * @brief Constructs a program timer with the specified timeout and resolution.
     * @param timeout Timeout value.
     * @param resolution Timer resolution. Default is milliseconds.
     */
    explicit ProgramTimer(const size_t timeout, const Resolution resolution = Resolution::MILLISECONDS)
        : m_timeout(timeout), m_resolution(resolution)
    {}

    explicit ProgramTimer(const ProgramTimer& other) = default;
    ProgramTimer& operator=(const ProgramTimer& other) = default;
    explicit ProgramTimer(ProgramTimer&& other) noexcept = default;
    ProgramTimer& operator=(ProgramTimer&& other) noexcept = default;

    ~ProgramTimer() = default;

    /**
     * @brief Checks if the timer has expired. If expired, the timer is automatically reset.
     * @return True if the timer has expired, false otherwise.
     * @note The timer is reset upon expiration, so subsequent calls will check for the next timeout interval.
     */
    bool check()
    {
        auto flag = m_check();
        if (flag) reset();
        return flag;
    }

    /**
     * @brief Returns true while the timer is not expired.
     * @return True if the timer is active, false if it has expired.
     * @note This operator does not reset the timer, so it can be used for non-destructive checks.
     */
    bool expired() const { return m_check(); }


    /**
     * @brief Returns true while the timer is not expired.
     * @return True if the timer is active, false if it has expired.
     * @note This operator does not reset the timer, so it can be used for non-destructive checks.
     */
    operator bool() const { return m_check(); }


    /**
     * @brief Sets the timeout value.
     * @param timeout Timeout value.
     */
    void setTimeout(const size_t timeout) { m_timeout = timeout; }

    /**
     * @brief Returns the current timeout value.
     * @return Timeout value.
     */
    size_t getTimeout() const { return m_timeout; }

private:
    size_t m_timeout;
    Resolution m_resolution;

    /**
     * @brief Checks if the timer has expired based on the current resolution.
     * @return True if the timer has expired, false otherwise.
     * @note This function does not reset the timer, so it can be used for non-destructive checks.
     */
    bool m_check() const
    {
        switch (m_resolution)
        {
            case Resolution::MICROSECONDS: return microseconds() >= m_timeout; break;
            case Resolution::MILLISECONDS: return milliseconds() >= m_timeout; break;
            case Resolution::SECONDS:      return seconds() >= m_timeout; break;
            default: return false;
        }

        return false;
    }
};
