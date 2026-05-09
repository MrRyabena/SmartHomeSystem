#pragma once

namespace shs
{
    template <typename Mutex_t>
    class MutexSafe;
}

/**
 * @brief Scope guard that locks a mutex on construction and unlocks it on destruction.
 * @tparam Mutex_t Mutex type used by the current platform.
 */
template <typename Mutex_t>
class shs::MutexSafe
{
public:
    /**
     * @brief Locks the given mutex for the lifetime of this guard.
     */
    explicit MutexSafe(Mutex_t &mutex) : m_mutex(mutex)
    {
#ifdef SHS_SF_FreeRTOS
        xSemaphoreTake(m_mutex, portMAX_DELAY);
#else
        m_mutex.lock();
#endif
    }

    /**
     * @brief Unlocks the guarded mutex.
     */
    ~MutexSafe()
    {
#ifdef SHS_SF_FreeRTOS
        xSemaphoreGive(m_mutex);
#else
        m_mutex.unlock();
#endif
    }

    /**
     * @brief Copying is disabled for mutex guards.
     */
    MutexSafe(const MutexSafe &) = delete;

    /**
     * @brief Copy assignment is disabled for mutex guards.
     */
    MutexSafe &operator=(const MutexSafe &) = delete;

    /**
     * @brief Transfers guard ownership without unlocking the mutex.
     */
    MutexSafe(MutexSafe &&other) noexcept : m_mutex(other.m_mutex) { other.m_mutex = nullptr; }

    /**
     * @brief Move assignment is disabled for mutex guards.
     */
    MutexSafe &operator=(MutexSafe &&other) = delete;

private:
    Mutex_t m_mutex;
};
