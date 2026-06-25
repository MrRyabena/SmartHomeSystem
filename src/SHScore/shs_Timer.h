#pragma once

#include <stddef.h>
#include <stdint.h>

#include "shs_ProgramTime.h"
#include "shs_Process.h"

namespace shs
{
    class Timer;

    namespace timer_resolution
    {
        static constexpr auto microseconds = shs::ProgramTime::s_microseconds;
        static constexpr auto milliseconds = shs::ProgramTime::s_milliseconds;
        static constexpr auto seconds = shs::ProgramTime::s_seconds;
    }
}



/**
 * @brief Periodic process adapter that calls another shs::Process on a fixed interval.
 */
class shs::Timer : public shs::Process
{
public:
    /**
     * @brief Creates a timer for a process with a chosen period and resolution.
     */
    Timer(const size_t T = 0, shs::Process* process = nullptr,
        decltype(shs::timer_resolution::milliseconds) resolution = shs::timer_resolution::milliseconds
    )
        : m_res_func(resolution), m_T(T), m_tmr(m_res_func()), m_process(process)
    {}

    /**
     * @brief Destroys the timer.
     */
    ~Timer() = default;

    /**
     * @brief Starts the wrapped process, if any.
     */
    void start() override { if (m_process) m_process->start(); };

    /**
     * @brief Triggers the wrapped process when the configured period has elapsed.
     */
    void tick() override { if (m_process && m_res_func() - m_tmr >= m_T) { m_process->tick(); m_tmr = m_res_func(); } }

    /**
     * @brief Stops the wrapped process, if any.
     */
    void stop() override { if (m_process) m_process->stop(); }

    /**
     * @brief Resets the internal timer to the current time.
     */
    void reset() { m_tmr = m_res_func(); };

    /**
     * @brief Updates the timer period.
     */
    void setPeriod(const size_t T) { m_T = T; }

private:
    decltype(shs::timer_resolution::microseconds)
        m_res_func;

    size_t m_T;  // period
    size_t m_tmr;

    shs::Process* m_process;
};
