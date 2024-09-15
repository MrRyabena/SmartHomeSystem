#pragma once

#include "shs_Task.h"
#include "shs_Process.h"
#include <memory>


namespace shs
{
    class ProcessTask;
}



class shs::ProcessTask : public shs::Task
{
public:
    ProcessTask(shs::Process* process)
        : Task(ProcessTask::processFunction, static_cast<void*>(this)),
        m_process(process) {}

    ~ProcessTask() { std::cout << "~ProcessTask()" << std::endl; }

    void start() { m_process->start(); }
    void stop() { m_process->stop(); }

    void setStop() {
        std::cout << "Stopping process..." << std::endl;
        m_running = false; // Убедитесь, что это состояние действительно меняется
    }

private:
    shs::Process* m_process;
    bool m_running = false;

    static void processFunction(void* param)
    {
        auto self = static_cast<shs::ProcessTask*>(param);
        self->m_running = true;
        self->start();
        while (self->m_running)
        {
            self->m_process->tick();
#ifdef SHS_SF_FreeRTOS
            vTaskDelay(1);
#endif
        }
        self->stop();
    }

    friend class TaskManager;
    friend class OS;
};


