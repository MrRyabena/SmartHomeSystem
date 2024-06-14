#pragma once

#include <stdint.h>

namespace shs { struct WeatherStationData; };

#pragma pack(push, 1)
struct shs::WeatherStationData
{
    float indoorTemperature{};
    float outdoorTemperature{};

   //float indoorHumidity{};
    float outdoorHumidity{};

    float pressure{};

    uint32_t time{};

    uint16_t illuminance{};

    bool isRain{};
};
#pragma pack(pop)

static_assert(alignof(shs::WeatherStationData) == 1);
static_assert(sizeof(shs::WeatherStationData) == 23);
