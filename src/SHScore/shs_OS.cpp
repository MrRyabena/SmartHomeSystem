#include "shs_OS.h"

shs::OS::OS(const uint8_t cores, const uint8_t threads, const size_t thread_stack_size)
    : m_cores(cores),
    m_threads(threads)
{

    m_handlers.reserve(cores * threads);

    for (uint8_t core = 0; core < m_cores; core++)
        for (uint8_t thread = 0; thread < m_threads; thread++)
        {

            auto ph = std::make_unique<shs::ProcessesHandler>();

            auto id = m_tm.addTask<shs::ProcessesHandler>(shs::ProcessTask(ph.get()));
            m_handlers.push_back(std::pair<std::unique_ptr<shs::Process>, shs::task::task_id_t>(std::move(ph), id));

        }
}


shs::OS::~OS()
{
    for (auto& x : m_handlers) static_cast<shs::ProcessTask*>(m_tm[x.second]->task.get())->setStop();
    //while (m_tm.getTaskCount()) m_tm.checkCompleted();
}


void shs::OS::addProcess(shs::Process* process, const uint8_t coreID, const uint8_t threadID)
{
    // if (coreID == 0xff)
    // {
    //     uint8_t min_ind{};
    //     uint16_t min_load = 0xffff;

    //     for (uint8_t i = 0; i < m_processes.size(); i++)
    //     {
    //         if (std::get<0>(m_processes[i])->size() < min_load)
    //         {
    //             min_load == std::get<0>(m_processes[i])->size();
    //             min_ind = i;
    //         }
    //     }


    //     std::get<0>(m_processes[min_ind])->attach(process);
    // }
}

void shs::OS::stop()
{
    std::cout << "STOP" << std::endl;
    for (auto& x : m_handlers) static_cast<shs::ProcessTask*>(m_tm[x.second]->task.get())->setStop();
    for (auto& x : m_handlers) m_tm[x.second]->handle->join();
}
