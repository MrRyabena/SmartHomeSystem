#pragma once

#include "shs_settings_private.h"

#ifdef SHS_FS_FreeRTOS

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#else

#include <chrono>
#include <mutex>
#include <unique_lock>

#endif

#include "shs_MutexSafe.h"

namespace shs
{
    namespace os_utils
    {

        inline void sleep_for(const size_t time) { vTaskDelay(pdMS_TO_TICKS(time)); }
        inline void sleep_for_ticks(TickType_t ticks) { vTaskDelay(time) };
        using mutex = SemaphoreHandle_t;
        using mutex_safe = shs::MutexSafe;

#else
        inline void sleep_for(const std::chrono::microseconds &value) { std::this_thread::sleep_for(std::chrono::microseconds(value)); }
        inline auto sleep_for_ticks = sleep_for;

        using mutex = std::mutex;
        using mutex_safe = std::unique_lock;
#endif
    }
}
