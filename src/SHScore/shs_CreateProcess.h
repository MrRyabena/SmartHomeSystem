#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
*/

#include "shs_Process.h"


namespace shs
{
    template <typename StartPtr, typename TickPtr, typename StopPtr>
    class CreateProcess;
}


/*
  The class creates a process from function pointer templates.
*/
template <typename StartPtr, typename TickPtr, typename StopPtr>
class shs::CreateProcess : public Process
{
public:
    CreateProcess(StartPtr start_f, TickPtr tick_f, StopPtr stop_f)
        : m_start_f(start_f), m_tick_f(tick_f), m_stop_f(stop_f)
    {}

    void start() override { m_start_f(); }
    void tick() override { m_tick_f(); }
    void stop() override { m_stop_f(); }

private:
    StartPtr m_start_f{};
    TickPtr m_tick_f{};
    StopPtr m_stop_f{};

};
