#include <iostream>
#include <string>
#include <fstream>
#include "..\SHSconfig.h"

int main()
{
    SHSconfig config;
    std::ofstream file;
    std::string fname;

    std::cout << "Registering a new device" << std::endl;
    std::cout << "Enter ID: ";
    int id{};
    std::cin >> id;
    config.ID = id;
    std::cout << "Enter name: ";

    for (auto i = 0; i < 10; i++)
    {
        char c{};
        std::cin >> c;
        if (c == ' ')
        {
            i--;
            continue;
        }
        if (c == ';')
        {
            config.name[i] = '\0';
            break;
        }
        config.name[i] = c;
    }

    std::cout << "Enter MAC address: ";
    for (auto i = 0; i < 6; i++)
    {
        int val{};
        std::string str{};
        std::cin >> str;
        val = stoi(str, nullptr, 16);
        config.MACaddress[i] = val;
    }

    std::cout << static_cast<int>(config.ID) << std::endl;
    printf(config.name);
    std::cout << std::endl;
    for (auto i = 0; i < 6; i++)
        std::cout << static_cast<int>(config.MACaddress[i]);

    fname = "../../devices/";
    fname += config.name;
    fname += "/data/config.shsf";
    file.open(fname, std::ios::trunc);
    uint8_t *ptr = (uint8_t *)&config;
    for (auto i = 0; i < sizeof(config); i++)
        file << *ptr++;
    file.close();

    std::ifstream cfile;
    cfile.open("../../devices/server/data/comConf.shsf");

    cfile.seekg(0, std::ios_base::end);
    int cfsize = cfile.tellg();
    cfile.seekg(0, std::ios_base::beg);
    SHSconfig *carr = new SHSconfig[cfsize / sizeof(SHSconfig)];

    ptr = (uint8_t *)carr;
    for (auto i = 0; i < cfsize; i++)
        cfile >> *ptr++;
    cfile.close();

    bool flag = false;
    for (auto i = 0; i < cfsize / sizeof(SHSconfig); i++)
    {
        if (carr[i].ID == config.ID)
        {
            carr[i] = config;
            flag = true;
            break;
        }
    }

    file.open("../../devices/server/data/comConf.shsf", std::ios::trunc);
    ptr = (uint8_t *)carr;
    for (auto i = 0; i < cfsize; i++)
        file << *ptr++;
    ptr = (uint8_t *)&config;
    if (!flag)
        for (auto i = 0; i < sizeof(SHSconfig); i++)
            file << *ptr++;
    file.close();

    return 0;
}
