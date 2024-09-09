#include "shs_OS.h"

shs::OS::OS(const uint8_t cores, const uint8_t threads, const size_t thread_stack_size)
    : m_cores(cores),
      m_threads(threads)
{

    m_processes.reserve(cores * threads);

    for (uint8_t core = 0; core < m_cores; core++)
        for (uint8_t thread = 0; thread < m_threads; thread++)
        {

            auto ph = std::make_unique<shs::ProcessesHandler>();
            auto task = std::make_shared<shs::ProcessTask>(
                ph.get(),
                0,
                1,
                core,
                thread_stack_size);

                std::cout << "Test" << std::endl;
            auto thr = std::make_unique<std::thread>(shs::ProcessTask::processFunction, task);
            
            

            
            //m_tm.addTask(*task);
            m_processes.push_back(std::tuple<std::unique_ptr<shs::ProcessesHandler>, std::shared_ptr<shs::ProcessTask>, std::unique_ptr<std::thread>>(std::move(ph), task, std::move(thr)));
            
        }
}


shs::OS::~OS() 
{
    for (auto &x : m_processes) std::get<1>(x)->m_running = false;
    //while (m_tm.getTaskCount()) m_tm.checkCompleted();
}


void shs::OS::addProcess(shs::Process *process, const uint8_t coreID, const uint8_t threadID)
{
    if (coreID == 0xff)
    {
        uint8_t min_ind{};
        uint16_t min_load = 0xffff;

        for (uint8_t i = 0; i < m_processes.size(); i++)
        {
            if (std::get<0>(m_processes[i])->size() < min_load)
            {
                min_load == std::get<0>(m_processes[i])->size();
                min_ind = i;
            }
        }
      

        std::get<0>(m_processes[min_ind])->attach(process);
    }
}

void shs::OS::stop()
{
    std::cout << "STOP" << std::endl;
    for (auto &x : m_processes) std::get<1>(x)->setStop();
    for (auto &x : m_processes) std::get<2>(x)->join();
}
