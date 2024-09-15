#pragma once

#include "shs_settings_private.h"
#include <memory> 

#ifdef SHS_SF_ARDUINO

#ifdef SHS_SF_AVR
#error "Not supported for AVR"
#endif

#if defined(SHS_SF_ESP8266) || defined(SHS_SF_ESP32)
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define SHS_SF_FreeRTOS
#endif

#else

#include <thread>

#endif

#include <vector>
#include <functional>

#include "shs_Task.h"
#include "shs_SortedBuf.h"
#include "shs_Process.h"
#include "shs_algorithm.h"

namespace shs
{
    class TaskManager;
    struct TM_data;
}

struct shs::TM_data
{
#ifdef SHS_SF_FreeRTOS
    TM_data(const shs::task::task_id_t id = 0, std::unique_ptr<shs::Task> task = {}, shs::task::handle_t handle = nullptr)
        : id(id), task(std::move(task)), handle(handle) {}
    TM_data(TM_data&& other) noexcept
        : id(other.id), task(std::move(other.task)), handle(other.handle) {}

    TM_data& operator=(TM_data&& other) noexcept {
        id = other.id;
        task = std::move(other.task);
        handle = other.handle;
        return *this;
    }
#else
    TM_data(const shs::task::task_id_t id = 0, std::unique_ptr<shs::Task> task = nullptr, shs::task::handle_t handle = nullptr)
        : id(id), task(std::move(task)), handle(std::move(handle)) {}
    TM_data(TM_data&& other) noexcept
        : id(other.id), task(std::move(other.task)), handle(std::move(other.handle)) {}

    TM_data& operator=(TM_data&& other) noexcept {
        id = other.id;
        task = std::move(other.task);
        handle = std::move(other.handle);
        return *this;
    }
#endif
    TM_data(const TM_data&) = delete;
    TM_data& operator=(const TM_data&) = delete;

    //TM_data& operator=(const TM_data&) = delete;

    shs::task::task_id_t       id;
    std::unique_ptr<shs::Task> task;
    shs::task::handle_t        handle;

    friend bool operator==(const TM_data& lhs, const TM_data& rhs) { return lhs.id == rhs.id; }
    friend bool operator!=(const TM_data& lhs, const TM_data& rhs) { return !(lhs == rhs); }
    friend bool operator< (const TM_data& lhs, const TM_data& rhs) { return lhs.id < rhs.id; }
    friend bool operator> (const TM_data& lhs, const TM_data& rhs) { return rhs < lhs; }
    friend bool operator<=(const TM_data& lhs, const TM_data& rhs) { return !(rhs < lhs); }
    friend bool operator>=(const TM_data& lhs, const TM_data& rhs) { return !(lhs < rhs); }
};

class shs::TaskManager
{
public:
    explicit TaskManager(const uint8_t cores = 1);
    ~TaskManager();


    template <class Data_t, class Task_t>
    shs::task::task_id_t addTask(const Task_t& task, const uint8_t core = 0xff);


    uint8_t deleteTask(const shs::task::task_id_t taskID);
    void checkCompleted();

    size_t getTaskCount() { return m_tasks.size(); };

private:

    friend class OS;
    shs::SortedBuf<shs::TM_data> m_tasks;

    uint8_t m_cores;
    std::vector<size_t> m_cores_load;

    void m_start_task(shs::TM_data& tm_data, const uint8_t coreID = 0, const shs::task::stack_size_t stack_size = 100, const shs::task::priority_t priority = 0);
    void m_end_task(shs::TM_data& tm_data);

    auto operator[](const shs::task::task_id_t id)
    {
        return shs::binary_search(m_tasks.begin(), m_tasks.end(), TM_data(id));
    }

};


template<class Data_t, class Task_t>
inline shs::task::task_id_t shs::TaskManager::addTask(const Task_t& task, const uint8_t core)
{
    uint8_t core_id{ core };

    if (core == 0xff)
    {
        size_t min_load = std::numeric_limits<uint32_t>::max();
        for (uint8_t i = 0; i < m_cores; i++)
            if (m_cores_load[i] < min_load)
            {
                min_load = m_cores_load[i];
                core_id = i;
            }
    }

    // auto ptr = ;
    shs::TM_data tm_data(0, std::make_unique<Task_t>(task));
    for (tm_data; shs::binary_search(m_tasks.begin(), m_tasks.end(), tm_data) != m_tasks.end(); tm_data.id++);

    auto it = m_tasks.attach(std::move(tm_data));

    std::cout << "This" << std::endl;

    m_start_task(*it, core_id, shs::TaskData<Data_t>::stack_size, shs::TaskData<Data_t>::priority);
    //tm_data.handle = std::move(std::make_unique<std::thread>(shs::Task::doTask, it->task.get()));
    std::cout << "ok" << std::endl;
    m_cores_load[core_id] += shs::TaskData<Data_t>::complexy;

    return it->id;
}

