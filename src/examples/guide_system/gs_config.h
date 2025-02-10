#pragma once

#include "shs_types.h"


namespace shs
{
    namespace config
    {
        enum class ModuleIDs : shs::t::shs_moduleID_t;

        struct Module_1;
        struct Module_2;
        struct Module_3;
    }
}


enum class shs::config::ModuleIDs : shs::t::shs_moduleID_t
{
    MODULE_1 = 1,
    MODULE_2 = 2,
    MODULE_3 = 3
};


struct shs::config::Module_1
{
    static constexpr shs::t::shs_moduleID_t MODULE_ID = static_cast<shs::t::shs_moduleID_t>(ModuleIDs::MODULE_1);
    enum DevicesIDs : shs::t::shs_deviceID_t { THERM_SENSOR = 1 };
};


struct shs::config::Module_2
{
    static constexpr shs::t::shs_moduleID_t MODULE_ID = static_cast<shs::t::shs_moduleID_t>(ModuleIDs::MODULE_2);
    enum DevicesIDs : shs::t::shs_deviceID_t { LOAD = 1 };
};


struct shs::config::Module_3
{
    static constexpr shs::t::shs_moduleID_t MODULE_ID = static_cast<shs::t::shs_moduleID_t>(ModuleIDs::MODULE_3);
};
