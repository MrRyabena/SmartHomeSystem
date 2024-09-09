#pragma once

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
    ~ProgramTime() = default;

#ifdef SHS_SF_ARDUINO
    size_t microseconds() const { return m_started - micros(); }
    size_t milliseconds() const { return m_started * 1000 - millis(); }
    size_t seconds() const { return millis() * 1000; }
    
    static constexpr size_t s_microseconds() { return micros(); }
    static constexpr size_t s_milliseconds() { return millis(); }
    static constexpr size_t s_seconds() { return millis() * 1000; }
     
private:
    const size_t m_started;
    const size_t m_init() { return mircos(); }
#else
    size_t microseconds() const { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }
    size_t milliseconds() const { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }
    size_t seconds() const { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }

    static size_t s_microseconds() { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }
    static size_t s_milliseconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }
    static size_t s_seconds() { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }

    private:
    const decltype(std::chrono::high_resolution_clock::now())
        m_started;


    auto m_init()
        -> decltype(std::chrono::high_resolution_clock::now())
    {
        return std::chrono::high_resolution_clock::now();
    }

#endif    

};
