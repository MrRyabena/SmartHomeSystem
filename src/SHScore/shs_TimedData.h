#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created for use in sensors-classes
*/

#include <stdint.h>
#include "shs_settings_private.h"

#ifdef SHS_SF_AVR
#include <shs_lib_AVR_STD_memory.h>
#else
#include <memory>
#endif 

#include "shs_ProgramTime.h"



namespace shs
{
    template<typename> class TimedData;
}

/**
 * @brief Expiring data container that invalidates stored values after a timeout.
 * @tparam DataT Type of the stored value.
 */
template<typename DataT>
class shs::TimedData
{
public:
    /**
     * @brief Creates a value container with the specified expiration time.
        * @param expiration_time Expiration timeout in milliseconds.
     */
    TimedData(const uint32_t expiration_time) : m_expiration_time(expiration_time), m_data_ptr(new DataT{})
    {
        m_timer.reset();
    }

    /**
     * @brief Releases the managed value if it exists.
     */
    ~TimedData() { if (m_data_ptr) delete m_data_ptr; }


    /**
     * @brief Sets the expiration duration.
        * @param expiration_time Expiration timeout in milliseconds.
     */
    void setExpiration(const uint32_t expiration_time) { m_expiration_time = expiration_time; }

    /**
     * @brief Returns the expiration duration.
        * @return Expiration timeout in milliseconds.
     */
    auto getExpiration() const { return m_expiration_time; }

    /**
     * @brief Returns the remaining time before expiration.
        * @return Remaining lifetime in milliseconds.
     */
    auto getRemainingExpiration() const { return m_expiration_time - m_timer.milliseconds(); }

    /**
     * @brief Stores a copy of new data and refreshes the timer.
        * @param data New value to copy into the container.
     */
    void update(const DataT& data);

    /**
     * @brief Stores moved data and refreshes the timer.
        * @param data New value to move into the container.
     */
    void update(DataT&& data);

    /**
     * @brief Returns the stored value.
        * @return Const reference to the stored value.
     */
    [[nodiscard]] const DataT& getData() const { return *m_data_ptr; }

    /**
     * @brief Resets the expiration timer.
     */
    void reset() { m_timer.reset(); }

    /**
     * @brief Reports whether a value is currently stored.
        * @return True when storage pointer is not null.
     */
    bool hasData() const { return m_data_ptr != nullptr; }

    /**
     * @brief Reports whether the stored value has expired.
        * @return True when there is no data or timeout has elapsed.
     */
    bool isExpired() const { return !hasData() || m_timer.milliseconds() > m_expiration_time; }

    /**
     * @brief Frees the stored value if it is expired.
        * @return True when data was released, false otherwise.
     */
    bool freeExpired();


    /**
     * @brief Returns true while the stored value is valid.
        * @return True when data exists and is not expired.
     */
    operator bool() const { return !isExpired(); }

    /**
     * @brief Returns the stored value by reference.
        * @return Reference to the stored value.
     */
    DataT& operator*() { return *m_data_ptr; }

    /**
     * @brief Returns the managed pointer.
        * @return Pointer to the stored value.
     */
    DataT* operator&() { return m_data_ptr; }

    /**
     * @brief Returns the managed pointer.
        * @return Pointer to the stored value.
     */
    DataT* operator->() { return m_data_ptr; }

    /**
     * @brief Returns the managed pointer.
        * @return Const pointer to the stored value.
     */
    const DataT* operator->() const { return m_data_ptr; }


private:
    /**
     * @brief Timer that tracks expiration.
     */
    shs::ProgramTime m_timer;

    /**
     * @brief Expiration duration in milliseconds.
     */
    uint32_t m_expiration_time;

    /**
     * @brief Pointer to the stored value.
     */
    DataT* m_data_ptr{};
};


template<typename DataT>
inline void shs::TimedData<DataT>::update(const DataT& data)
{
    if (m_data_ptr) *m_data_ptr = data;
    else m_data_ptr = new DataT{ data };

    m_timer.reset();
}


template<typename DataT>
inline void shs::TimedData<DataT>::update(DataT&& data)
{
    if (m_data_ptr) *m_data_ptr = std::move(data);
    else m_data_ptr = new DataT{ std::move(data) };

    m_timer.reset();
}


template<typename DataT>
inline bool shs::TimedData<DataT>::freeExpired()
{
    if (hasData() && isExpired())
    {
        delete m_data_ptr;
        m_data_ptr = nullptr;

        return true;
    }

    return false;
}
