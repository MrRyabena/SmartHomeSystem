#pragma once

#include <memory>
#include <vector>
#include <initializer_list>

#include <shs_Process.h>
#include <shs_Load.h>
#include <shs_ProgramTimer.h>
#include <shs_types.h>


namespace shs
{
    class Sunrise;
}


class shs::Sunrise : public shs::Process
{
public:
    explicit Sunrise(std::initializer_list<std::shared_ptr<shs::Load>> loads)
        : m_loads(loads), m_timer(0)
    {}

    ~Sunrise() override = default;

    void sunrise(shs::t::shs_time_t time);
    void sundown(shs::t::shs_time_t time);

    void attachLoad(std::shared_ptr<shs::Load> load) { m_loads.push_back(load); }

    void start() override {}
    void tick() override;
    void stop() override {}

protected:
    std::vector<std::shared_ptr<shs::Load>> m_loads;
    shs::ProgramTimer m_timer;
    uint16_t m_iteration{};
    int8_t m_incr{};

    void m_on_loads(uint16_t value);
};



