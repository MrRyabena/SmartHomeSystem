#pragma once
#include "../../SHScore/SHSsettings_private.h"

namespace shs::config
{

    namespace SmartModulesID
    {
        enum SmartModulesID : shs::settings::shs_ModuleID_t
        {
            SmartServer = 4,
            SmartBulb = 5,
            SmartLight = 6,
            SmartFan = 7,
            App = 10,
        };
    };

    namespace APIID
    {
        enum APIID : shs::settings::shs_ID_t
        {
            lBulb_apiID = -11,
        };
    };

    namespace SmartServerAPI
    {
        enum SmartServerAPI : uint8_t
        {
            getReport,
            report,

            getStatus,
            status,

            getMode,
            mode,

            getTherm,
            therm,

            getPhoto,
            photo,

            setFan,
            setLed,
            setBulb,
            setHalogen,
        };
    };
};
