#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.1.0 — created.
*/

#include "shs_ProgramTime.h"



namespace shs
{
    class ProgramTimer;
}


class shs::ProgramTimer : public shs::ProgramTime
{
public:
    enum class Resolution : uint8_t { MICROSECONDS, MILLISECONDS, SECONDS };

    ProgramTimer(const size_t timeout, const Resolution resolution = Resolution::MILLISECONDS)
        : m_timeout(timeout), m_resolution(resolution)
    {}

    ~ProgramTimer() = default;

    bool check()
    {
        auto flag = m_check();
        if (flag) reset();
        return flag;
    }


    operator bool() const { return m_check(); }

    void setTimeout(const size_t timeout) { m_timeout = timeout; }
    size_t getTimeout() const { return m_timeout; }

private:
    size_t m_timeout;
    const Resolution m_resolution;

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