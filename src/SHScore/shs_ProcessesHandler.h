#pragma once

#include "shs_Process.h"
#include "shs_SortedBuf.h"
#include "shs_Task.h"

namespace shs
{
    class ProcessesHandler;
}

template <>
struct shs::TaskData<shs::ProcessesHandler>
{
    static constexpr shs::task::stack_size_t stack_size = 100;   // In words
    static constexpr shs::task::priority_t   priority = 0;       // 0 is the highest priority
    static constexpr shs::task::complexy_t   complexy = 1;       // 1 is the lowest complexity
};

class shs::ProcessesHandler : public shs::Process, public shs::SortedBuf<shs::Process*>
{
public:
    void start() override { for (auto x : m_srtdbuf) x->start(); }
    void tick()  override { for (auto x : m_srtdbuf) x->tick(); }
    void stop()  override { for (auto x : m_srtdbuf) x->stop(); }
};
