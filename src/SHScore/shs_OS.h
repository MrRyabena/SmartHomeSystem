
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

    void addProcess(shs::Process* process, const uint8_t coreID = 0xff, const uint8_t threadID = 0xff);

    void stop();

private:
    const uint8_t m_cores;
    const uint8_t m_threads;

    std::vector<std::pair<std::unique_ptr<shs::Process>, shs::task::task_id_t>> m_handlers;

public:
    shs::TaskManager m_tm;
};
