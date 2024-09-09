#pragma once

#include "shs_Process.h"
#include "shs_SortedBuf.h"

namespace shs
{
    class ProcessesHandler;
}


class shs::ProcessesHandler : public shs::Process, public shs::SortedBuf<shs::Process *>
{
public:
    void start() override { for (auto x : m_srtdbuf) x->start(); }
    void tick()  override { for (auto x : m_srtdbuf) x->tick(); }
    void stop()  override { for (auto x : m_srtdbuf) x->stop(); }
};
