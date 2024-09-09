#pragma once

#include "shs_settings_private.h"
#include <memory> // Для умных указателей

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
}

class shs::TaskManager
{
public:
    explicit TaskManager(const uint8_t cores = 1);
    ~TaskManager();

    shs::task::task_id_t addTask(const shs::Task &task, const bool set_core_auto = false);
    uint8_t deleteTask(const shs::task::task_id_t taskID);
    void checkCompleted();

    size_t getTaskCount() { return m_tasks.size(); };

private:
    struct TM_data
    { 
        

    };
    shs::SortedBuf<std::shared_ptr<shs::Task>, std::function<bool(const std::shared_ptr<shs::Task>, const std::shared_ptr<shs::Task>)>> m_tasks;

    uint8_t m_cores;
    shs::task::task_id_t nextID;
    std::vector<uint32_t> m_cores_load;

    static void m_loop(void *ptr);
    void m_start_task(shs::Task &task);
    void m_end_task(shs::Task &task);
};
