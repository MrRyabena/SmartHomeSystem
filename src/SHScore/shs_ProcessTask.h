#pragma once

#include "shs_Task.h"
#include "shs_Process.h"
#include <memory>


namespace shs
{
    class ProcessTask;
}

class shs::ProcessTask //: public shs::Task
{
public:
    ProcessTask(shs::Process* process,
                shs::task::priority_t priority = 0,
                shs::task::complexy_t complexity = 1,
                shs::task::coreID_t coreID = 0,
                shs::task::stack_size_t stack_size = 100) :
        // : Task(ProcessTask::processFunction,
        //        static_cast<void*>(this),
        //        priority,
        //        complexity,
        //        coreID,
        //        stack_size),
         m_process(process)
    {}

    ~ProcessTask() { std::cout << "~ProcessTask()" << std::endl;}

    void start() { m_process->start(); }
    void stop() { m_process->stop(); }

      void setStop() {
       std::cout << "Stopping process..." << std::endl;
       m_running = false; // Убедитесь, что это состояние действительно меняется
   }

private:
    shs::Process* m_process;
    bool m_running = false;

    static void processFunction(std::shared_ptr<shs::ProcessTask> self)
    {
       // auto self = static_cast<std::shared_ptr<shs::ProcessTask>>(param);
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
 