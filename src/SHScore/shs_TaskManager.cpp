#include "shs_TaskManager.h"

shs::TaskManager::TaskManager(const uint8_t cores)
    : m_cores(cores), m_cores_load(cores, 0), nextID(1),
      m_tasks([](const std::shared_ptr<shs::Task> v1, const std::shared_ptr<shs::Task> v2)
              { return v1->id < v2->id; })
{
    // shs::Task TMloop_task(
    //     &shs::TaskManager::m_loop,
    //     this,
    //     10,
    //     1,
    //     0,
    //     20,
    //     "TMloop");

    // addTask(TMloop_task);
}

#include <iostream>
shs::TaskManager::~TaskManager()
{
    std::cout << "~TaskManager()" << std::endl;
    //for (auto &x : m_tasks) if (x->handle && x->handle->joinable()) x->handle->join();
    //checkCompleted();
}

shs::task::task_id_t shs::TaskManager::addTask(const shs::Task &task, const bool set_core_auto)
{
    // if (set_core_auto)
    // {
    //     uint8_t core_id{};
    //     uint32_t min_load = std::numeric_limits<uint32_t>::max();
    //     for (uint8_t i = 0; i < m_cores; i++)
    //         if (m_cores_load[i] < min_load)
    //         {
    //             min_load = m_cores_load[i];
    //             core_id = i;
    //         }
    //     task.coreID = core_id;
    // }

    // for (task.id; shs::binary_search(m_tasks.begin(), m_tasks.end(), &task) != m_tasks.end(); task.id++)
    //     ;

    

    //auto task_ptr = std::make_shared<shs::Task>(std::move(task));
    // task_ptr->id = nextID++;

    // m_start_task(*task_ptr);
    // m_tasks.attach(task_ptr);
    // m_cores_load[task_ptr->coreID] += task_ptr->complexy;

    // return task_ptr->id;
    return 0;
}

#include <iostream>
uint8_t shs::TaskManager::deleteTask(const shs::task::task_id_t taskID)
{
    // auto task = std::make_shared<shs::Task>(nullptr);
    // task->id = taskID;
    
    // auto it = shs::binary_search(m_tasks.begin(), m_tasks.end(), task,
    //                              [](const std::shared_ptr<shs::Task> v1, const std::shared_ptr<shs::Task> v2)
    //           { return v1->id < v2->id; });

    // if (it != m_tasks.end())
    // {       
    //     m_end_task(**it);
    //     m_cores_load[(*it)->coreID] -= (*it)->complexy;
    //     m_tasks.detach(*it);
    //     return 0;
    // }
    return 1;
}

void shs::TaskManager::checkCompleted()
{
    // std::vector<shs::task::task_id_t> ids;
    // for (auto &x : m_tasks)
    //     if (x->isCompleted) ids.push_back(x->id);
    

    // for (auto x : ids) deleteTask(x);
}

void shs::TaskManager::m_start_task(shs::Task &task)
{
#ifdef SHS_SF_FreeRTOS
#ifdef SHS_SF_ESP32
    // Create a new task using xTaskCreatePinnedToCore
    xTaskCreatePinnedToCore(
        shs::Task::doTask, // Pointer to the task function
        nullptr,           // Name of the task
        task.stack_size,   // Stack size in words
        &task,             // Task input parameters
        task.priority,     // Task priority
     //   &task.handle,      // Pointer to store the task handle
        task.coreID        // Core where the task should run
    );
#else
    xTaskCreate(
        shs::Task::doTask, // Pointer to the task function
        nullptr,           // Name of the task
        task.stack_size,   // Stack size in words
        &task,             // Task input parameters
        task.priority,     // Task priority
       // &task.handle       // Pointer to store the task handle
    );
#endif

#elif defined(SHS_SF_AVR)

#error "Not implemented for AVR"

#else
    //task.handle = std::make_unique<std::thread>(shs::Task::doTask, &task);
#endif
}

void shs::TaskManager::m_loop(void *ptr)
{
    // auto self = static_cast<shs::TaskManager *>(ptr);
    // while (true)
    // {
    //     self->checkCompleted();
    //     // shs::Task::sleep_for_ticks(100);
    //     std::this_thread::sleep_for(std::chrono::microseconds(100));
    // }
}

void shs::TaskManager::m_end_task(shs::Task &task)
{
#ifdef SHS_SF_FreeRTOS
    if (task.handle != nullptr)
    {
        vTaskDelete(task.handle);
        task.handle = nullptr;
    }
#elif defined(SHS_SF_AVR)
#error "Not implemented for AVR"
#else
   // if (task.handle != nullptr)
   // {
        //  task.handle->request_stop();
       // if (task.handle && task.handle->joinable()) task.handle->join();
   // }
#endif
}
