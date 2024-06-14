#include <iostream>
#include "shs_WeatherStationData.h"


int main()
{
    std::cout << sizeof(shs::WeatherStationData) << ' ' << alignof(shs::WeatherStationData) << std::endl;

    shs::WeatherStationData wsd;
    wsd.isRain = true;

    std::cout << (int)*((uint8_t *) &wsd + 24) << std::endl;

    return 0;

}