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
    template<> struct TaskData;
    class Task;


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

        using function_t = void (*)(void*);
        using name_t = const char*;
        using stack_size_t = size_t;
        using parameters_t = void*;
        using priority_t = ubase_type_t;
        using coreID_t = base_type_t;

        using complexy_t = ubase_type_t;
        using task_id_t = ubase_type_t;
    };
};
#include <iostream>

template <>
struct shs::TaskData<shs::Task>
{
    static constexpr shs::task::stack_size_t stack_size = 100;   // In words
    static constexpr shs::task::priority_t   priority = 0;       // 0 is the highest priority
    static constexpr shs::task::complexy_t   complexy = 1;       // 1 is the lowest complexity
}


class shs::Task
{
public:
    explicit Task(shs::task::function_t set_function, shs::task::parameters_t set_parameters = nullptr)
        : function(set_function), parameters(set_parameters), isCompleted(false)
    {}

    ~Task() { std::cout << "~Task()" << std::endl; }


    bool isCompleted() const { return m_completed; }


    shs::task::function_t function;       // Function pointer
    shs::task::parameters_t parameters;   // <void*>
private:
    volatile bool m_completed;

    friend class TaskManager;
    friend class OS;

    static void doTask(void* args)
    {
        auto self = static_cast<shs::Task*>(args);
        self->function(self->parameters);
        self->m_completed = true;
    }
};
