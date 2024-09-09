#pragma once

#include "shs_settings_private.h"

#ifdef SHS_SF_ARDUINO

#ifdef SHS_SF_AVR
#endif

#if defined(SHS_SF_ESP8266) || defined(SHS_SF_ESP32)
#include <freertos.h>
#define SHS_SF_FreeRTOS
#endif

#else
#include <thread>
#include <memory>
#endif

namespace shs
{
    struct Task;
    namespace task
    {

#ifdef SHS_SF_FreeRTOS
        using base_type_t = BaseType_t;
        using ubase_type_t = uBaseType_t;

        using handle_t = TaskHandle_t;
#else
        using base_type_t = int32_t;
        using ubase_type_t = uint32_t;

        using handle_t = std::unique_ptr<std::thread>;
#endif

        using function_t = void (*)(void *);
        using name_t = const char *;
        using stack_size_t = size_t;
        using parameters_t = void *;
        using priority_t = ubase_type_t;
        using coreID_t = base_type_t;

        using complexy_t = ubase_type_t;

        using task_id_t = ubase_type_t;
    }
}
#include <iostream>
struct shs::Task
{
    explicit Task(
        shs::task::function_t set_function,
        shs::task::parameters_t set_parameters = nullptr,
        shs::task::priority_t set_priority = 0,
        shs::task::complexy_t set_complexy = 0,

        shs::task::coreID_t set_coreID = 0,
        shs::task::stack_size_t set_stack_size = 100)
        : function(set_function),
          stack_size(set_stack_size),
          parameters(set_parameters),
          priority(set_priority),
          //handle{},
          coreID(set_coreID),

          complexy(set_complexy),
          id{},
          isCompleted(false)
    {
    }

    // Task(Task&& other) noexcept
    //     : function(std::move(other.function)),
    //       stack_size(other.stack_size),
    //       parameters(other.parameters),
    //       priority(other.priority),
    //       //handle(std::move(other.handle)),
    //       coreID(other.coreID),
    //       complexy(other.complexy),
    //       id(other.id),
    //       isCompleted(other.isCompleted)
    // {
    //     other.isCompleted = false; 

    // }

    
    ~Task() { 
        std::cout << "~Task()" << std::endl;
        //if (handle && handle->joinable()) {
       // handle->joinable(); // Ожидание завершения потока
   //}
   }
    //Task(const Task&) = delete;

    shs::task::function_t function;       // Function pointer
    shs::task::stack_size_t stack_size;   // In words
    shs::task::parameters_t parameters;   // (void*)
    shs::task::priority_t priority;       // 0 is the highest priority
   // shs::task::handle_t handle;
    shs::task::coreID_t coreID;

    shs::task::complexy_t complexy;       // 1 is the lowest complexity
    shs::task::ubase_type_t id;           // Task ID assigned by the task manager
    volatile bool isCompleted;

#ifdef SHS_FS_FreeRTOS
    static constexpr void sleep_for(const size_t t) { vTaskDelay(pdMS_TO_TICKS(t)); }
    static constexpr void (*sleep_for_ticks)(TickType_t) = &vTaskDelay;
#else
    //static constexpr void (*sleep_for)(const std::chrono::microseconds & value) = &std::this_thread::sleep_for(std::chrono::microseconds(value));
    //static constexpr auto sleep_for_ticks = sleep_for;
#endif

    bool operator<(const shs::Task &other) const { return id < other.id; }
    bool operator>(const shs::Task &other) const { return id > other.id; }
    bool operator==(const shs::Task &other) const { return id == other.id; }
    bool operator!=(const shs::Task &other) const { return !operator==(other); }

private:
    shs::task::ubase_type_t m_taskID{};
    friend class TaskManager;
    friend class OS;

    static void doTask(void *args)
    {
        auto self = static_cast<shs::Task *>(args);
        self->function(self->parameters);
        self->isCompleted = true;
    }
};
