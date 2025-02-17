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



class shs::Timer : public shs::Process
{
public:
    Timer(const size_t T = 0, shs::Process* process = nullptr,
        decltype(shs::timer_resolution::milliseconds) resolution = shs::timer_resolution::milliseconds
    )
        : m_res_func(resolution), m_T(T), m_tmr(m_res_func()), m_process(process)
    {}

    ~Timer() = default;

    void start() override { if (m_process) m_process->start(); };
    void tick() override { if (m_process && m_res_func() - m_tmr >= m_T) { m_process->tick(); m_tmr = m_res_func(); } }
    void stop() override { if (m_process) m_process->stop(); }

    void reset() { m_tmr = m_res_func(); };

    void setPeriod(const size_t T) { m_T = T; }

private:
    decltype(shs::timer_resolution::microseconds)
        m_res_func;

    size_t m_T;  // period
    size_t m_tmr;

    shs::Process* m_process;
};
