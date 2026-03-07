#pragma once

#include <GRGB.h>

#include <shs_Process.h>


namespace shs
{
    class GRGB_Effect;
}


class shs::GRGB_Effect : public shs::Process
{
public:
    GRGB_Effect(GRGB& grgb) : m_grgb(grgb) {}
    ~GRGB_Effect() = default;

protected:
    GRGB& m_grgb;
};
