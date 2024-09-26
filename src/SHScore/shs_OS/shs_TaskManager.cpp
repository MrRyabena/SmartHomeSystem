#include "shs_TaskManager.h"

shs::TaskManager::TaskManager(const uint8_t cores)
    : m_cores(cores), m_cores_load(cores, 0) {}

#include <iostream>
shs::TaskManager::~TaskManager()
{
    std::cout << "~TaskManager()" << std::endl;
    checkCompleted();
}

#include <iostream>
uint8_t shs::TaskManager::deleteTask(const shs::task::task_id_t taskID)
{
    shs::TM_data tm(taskID);

    auto it = shs::binary_search(m_tasks.begin(), m_tasks.end(), tm);

    if (it != m_tasks.end())
    {
        m_end_task(*it);
        //m_cores_load[(*it)->coreID] -= (*it)->complexy;
        m_tasks.detach(*it);
        return 0;
    }
    return 1;
}


void shs::TaskManager::checkCompleted()
{
    std::vector<shs::task::task_id_t> ids;
    for (auto& x : m_tasks)
        if (x.task->isCompleted()) ids.push_back(x.id);


    for (auto x : ids) deleteTask(x);
}


void shs::TaskManager::m_start_task(TM_data& tm_data, const uint8_t coreID, const shs::task::stack_size_t stack_size, const shs::task::priority_t priority)
{
#ifdef SHS_SF_FreeRTOS
#ifdef SHS_SF_ESP32
    // Create a new task using xTaskCreatePinnedToCore
    xTaskCreatePinnedToCore(
        shs::Task::doTask,         // Pointer to the task function
        nullptr,                   // Name of the task
        stack_size,                // Stack size in words
        tm_data.task.get(),        // Task input parameters
        tm_data.task->priority,    // Task priority
        tm_data.handle,      // Pointer to store the task handle
        coreID                     // Core where the task should run
    );
#else
    xTaskCreate(
        shs::Task::doTask,         // Pointer to the task function
        nullptr,                   // Name of the task
        stack_size,                // Stack size in words
        tm_data.task.get(),        // Task input parameters
        tm_data.task->priority,    // Task priority
        tm_data.task->handle,      // Pointer to store the task handle
        );
#endif

#elif defined(SHS_SF_AVR)

#error "Not implemented for AVR"

#else
    tm_data.handle = std::move(std::make_unique<std::thread>(shs::Task::doTask, tm_data.task.get()));
    std::cout << "and this" << std::endl;
#endif
}


void shs::TaskManager::m_end_task(TM_data& tm_data)
{
#ifdef SHS_SF_FreeRTOS
    if (tm_data.handle != nullptr)
    {
        vTaskDelete(tm_data.handle);
        tm_data.handle = nullptr;
    }
#elif defined(SHS_SF_AVR)
#error "Not implemented for AVR"
#else
    if (tm_data.handle && tm_data.handle->joinable()) tm_data.handle->join();
#endif
}

