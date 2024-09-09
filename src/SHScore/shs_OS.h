
#include "shs_Process.h"
#include "shs_ProcessesHandler.h"
#include "shs_ProcessTask.h"
#include "shs_Task.h"
#include "shs_TaskManager.h"

// #include <thread>
// #include <chrono>
#include <vector>
#include <utility>
#include <stddef.h>
#include <stdint.h>
#include <tuple>

namespace shs
{
    class OS;
}

class shs::OS
{
public:
    explicit OS(const uint8_t cores = 1, const uint8_t threads = 1, const size_t thread_stack_size = 1000);
    ~OS();

    void addProcess(shs::Process *process, const uint8_t coreID = 0xff, const uint8_t threadID = 0xff);

    void stop();

private:
    const uint8_t m_cores;
    const uint8_t m_threads;
    
    std::vector<std::tuple<std::unique_ptr<shs::ProcessesHandler>, std::shared_ptr<shs::ProcessTask>, std::unique_ptr<std::thread>>> m_processes;
    //shs::TaskManager m_TM;
    // static constexpr void (*sleep_for)(size_t value) = std::this_thread::sleep_for(std::chrono::milliseconds(value))
public:
    //shs::TaskManager m_tm;
};
