#pragma once


/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — function names have been changed, optimized, fixed bugs, tested.
*/

#include <stdint.h>
#include <stddef.h>

#include "shs_settings_private.h"

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#else
#include <chrono>    
#endif

namespace shs
{
    class ProgramTime;
}


class shs::ProgramTime
{
public:

    ProgramTime() : m_started(m_init()) {}

    ProgramTime(const ProgramTime& other) : m_started(other.m_started) {}
    ProgramTime(ProgramTime&& other) : m_started(other.m_started) { other.m_started = {}; }

    ProgramTime& operator=(const ProgramTime& other) { if (this != &other) m_started = other.m_started; return *this; }
    ProgramTime& operator=(ProgramTime&& other) { if (this != &other) m_started = other.m_started; other.m_started = {}; return *this; }
    ~ProgramTime() = default;

    void reset() { m_started = m_init(); }

#ifdef SHS_SF_ARDUINO
    size_t microseconds() const { return micros() - m_started / 1000; }
    size_t milliseconds() const { return millis() - m_started; }
    size_t seconds() const { return (millis() - m_started) / 1000; }

    static size_t s_microseconds() { return micros(); }
    static size_t s_milliseconds() { return millis(); }
    static size_t s_seconds() { return millis() * 1000; }

private:
    size_t m_started;
    const size_t m_init() { return millis(); } // micros(); }
#else
    size_t microseconds() const { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }
    size_t milliseconds() const { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }
    size_t seconds() const { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }

    static size_t s_microseconds() { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }
    static size_t s_milliseconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }
    static size_t s_seconds() { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }

private:
    decltype(std::chrono::high_resolution_clock::now())
        m_started;


    auto m_init() -> decltype(std::chrono::high_resolution_clock::now())
    {
        return std::chrono::high_resolution_clock::now();
    }

#endif    

};
