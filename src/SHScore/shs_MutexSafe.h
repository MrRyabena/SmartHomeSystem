#pragma once

namespace shs
{
    template <typename Mutex_t>
    class MutexSafe;
}

template <typename Mutex_t>
class shs::MutexSafe
{
public:
    explicit MutexSafe(Mutex_t &mutex) : m_mutex(mutex)
    {
#ifdef SHS_SF_FreeRTOS
        xSemaphoreTake(m_mutex, portMAX_DELAY);
#else
        m_mutex.lock();
#endif
    }

    ~MutexSafe()
    {
#ifdef SHS_SF_FreeRTOS
        xSemaphoreGive(m_mutex);
#else
        m_mutex.unlock();
#endif
    }

    MutexSafe(const MutexSafe &) = delete;
    MutexSafe &operator=(const MutexSafe &) = delete;

    MutexSafe(MutexSafe &&other) noexcept : m_mutex(other.m_mutex) { other.m_mutex = nullptr; }
    MutexSafe &operator=(MutexSafe &&other) = delete;

private:
    Mutex_t m_mutex;
};
