#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created for use in sensors-classes
*/

#include <stdint.h>
#include <memory>

#include "shs_ProgramTime.h"



namespace shs
{
    template<typename> class TimedData;
}

/*
  Container class for storing data with expiration time control.
  This class ensures that stored data remains valid only for a specified time period.
  When the expiration time is reached, the data is considered outdated and can be freed.

  Template parameter DataT defines the type of stored data.
*/
template<typename DataT>
class shs::TimedData
{
public:
    TimedData(const uint32_t expiration_time) : m_expiration_time(expiration_time), m_data_ptr(new DataT{})
    {
        m_timer.reset();
    }

    ~TimedData() { if (m_data_ptr) delete m_data_ptr; }


    void setExpiration(const uint32_t expiration_time) { m_expiration_time = expiration_time; }
    auto getExpiration() const { return m_expiration_time; }
    auto getRemainingExpiration() const { return m_expiration_time - m_timer.milliseconds(); }

    void update(const DataT& data);
    void update(DataT&& data);
    [[nodiscard]] const DataT& getData() const { return *m_data_ptr; }
    void reset() { m_timer.reset(); }

    bool hasData() const { return m_data_ptr != nullptr; }
    bool isExpired() const { return !hasData() || m_timer.milliseconds() > m_expiration_time; }
    bool freeExpired();


    operator bool() const { return !isExpired(); }

    DataT& operator*() { return *m_data_ptr; }
    DataT* operator&() { return m_data_ptr; }
    DataT* operator->() { return m_data_ptr; }
    const DataT* operator->() const { return m_data_ptr; }


private:
    shs::ProgramTime m_timer;
    uint32_t m_expiration_time;
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
