#pragma once

#include "shs_types.h"


namespace shs
{
    namespace config
    {
        enum class ModuleIDs : shs::t::shs_moduleID_t;

        struct Module_1_sensor;
        struct Module_2_load;
        struct Module_3_gui;
    }
}


enum class shs::config::ModuleIDs : shs::t::shs_moduleID_t
{
    MODULE_1_SENSOR = 1,
    MODULE_2_LOAD = 2,
    MODULE_3_GUI = 3
};


struct shs::config::Module_1_sensor
{
    static constexpr shs::t::shs_moduleID_t MODULE_ID = static_cast<shs::t::shs_moduleID_t>(ModuleIDs::MODULE_1_SENSOR);
    enum DevicesIDs : shs::t::shs_deviceID_t { THERM_SENSOR = 1 };
};


struct shs::config::Module_2_load
{
    static constexpr shs::t::shs_moduleID_t MODULE_ID = static_cast<shs::t::shs_moduleID_t>(ModuleIDs::MODULE_2_LOAD);
    enum DevicesIDs : shs::t::shs_deviceID_t { LOAD = 1 };
};


struct shs::config::Module_3_gui
{
    static constexpr shs::t::shs_moduleID_t MODULE_ID = static_cast<shs::t::shs_moduleID_t>(ModuleIDs::MODULE_3_GUI);
};
