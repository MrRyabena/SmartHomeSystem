#include <iostream>
#include <fstream>
#include <string>

#include "shs_WeatherStationData.h"
#include "../../SHScore/shs_CRC.h"

#include <stdint.h>

int main()
{
    std::fstream file;
    std::string name;
    
    std::cin >> name;

    file.open(name, std::ios::in);

    shs::WeatherStationData wsd;
    while (!file.eof())
    {
        wsd = {};
        file.read((char *) &wsd, sizeof(wsd));

        std::cout << "inTemp:    " <<
            wsd.indoorTemperature <<
            "\noutTemp:   " <<
            wsd.outdoorTemperature <<
            "\noutHum:    " <<
            wsd.outdoorHumidity <<
            "\npressure:  " <<
            wsd.pressure <<
            "\ntime:      " <<
            wsd.time <<
            "\nillum:     " <<
            wsd.illuminance <<
            "\nisRain:    " <<
            wsd.isRain <<
            "\n\n" << std::endl;

        uint32_t crc_val{};
        file.read((char *) &crc_val, sizeof(crc_val));

    }

    return 0;
}