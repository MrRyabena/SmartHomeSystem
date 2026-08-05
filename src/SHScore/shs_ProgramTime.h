#pragma once


/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — function names have been changed, optimized, fixed bugs, tested.
    v2.3.0 — updated docs.
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


/**
 * @brief Stopwatch-style utility for measuring elapsed time.
 */
class shs::ProgramTime
{
public:
    /**
     * @brief Starts measuring time from the current moment.
     */
    ProgramTime() : m_started(m_init()) {}

    /**
     * @brief Copies the start timestamp from another instance.
     */
    ProgramTime(const ProgramTime& other) : m_started(other.m_started) {}

    /**
     * @brief Moves the start timestamp from another instance.
     */
    ProgramTime(ProgramTime&& other) : m_started(other.m_started) { other.m_started = {}; }

    /**
     * @brief Copies the start timestamp from another instance.
     */
    ProgramTime& operator=(const ProgramTime& other) { if (this != &other) m_started = other.m_started; return *this; }

    /**
     * @brief Moves the start timestamp from another instance.
     */
    ProgramTime& operator=(ProgramTime&& other) { if (this != &other) m_started = other.m_started; other.m_started = {}; return *this; }

    /**
     * @brief Destroys the timer state.
     */
    ~ProgramTime() = default;

    /**
     * @brief Resets the start timestamp to the current moment.
     */
    void reset() { m_started = m_init(); }

#ifdef SHS_SF_ARDUINO
    /**
     * @brief Returns elapsed time in microseconds.
     */
    size_t microseconds() const { return micros() - m_started; }

    /**
     * @brief Returns elapsed time in milliseconds.
     */
    size_t milliseconds() const { return microseconds() / 1000; }

    /**
     * @brief Returns elapsed time in seconds.
     */
    size_t seconds() const { return milliseconds() / 1000; }

    /**
     * @brief Returns the current system time in microseconds.
     */
    static size_t s_microseconds() { return micros(); }

    /**
     * @brief Returns the current system time in milliseconds.
     */
    static size_t s_milliseconds() { return millis() / 1000; }

    /**
     * @brief Returns the current system time in seconds.
     */
    static size_t s_seconds() { return millis() / 1000000; }

private:
    size_t m_started;
    const size_t m_init() { return micros(); }
#else
    /**
     * @brief Returns elapsed time in microseconds.
     */
    size_t microseconds() const { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }

    /**
     * @brief Returns elapsed time in milliseconds.
     */
    size_t milliseconds() const { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }

    /**
     * @brief Returns elapsed time in seconds.
     */
    size_t seconds() const { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_started).count(); }

    /**
     * @brief Returns the current system time in microseconds.
     */
    static size_t s_microseconds() { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }

    /**
     * @brief Returns the current system time in milliseconds.
     */
    static size_t s_milliseconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }

    /**
     * @brief Returns the current system time in seconds.
     */
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
