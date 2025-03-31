#include "SHScore/SHSID.h"
#include <iostream>
#include <cassert>
#include <stdint.h>

int main()
{
    uint8_t module = 0xcd;
    uint8_t device = 0x12;
    int16_t api = -110;
    
    //std::cout << std::hex << static_cast<int>(module) << static_cast<int>(device) << api << std::endl;
    //std::cout << (((uint32_t)module << 24) | ((uint32_t)device << 16) | (api & 0xffff)) << std::endl;

    shs::ID id(module, device, api);
    //std::cout << std::hex << id.id << std::endl;

    assert(id.getModuleID() == module);
    assert(id.getDeviceID() == device);
    assert(id.getAPI() == api);

    shs::ID newID;
    newID.setModuleID(module).setDeviceID(device).setAPI(api);
    assert(newID.getModuleID() == module);
    assert(newID.getDeviceID() == device);
    assert(newID.getAPI() == api);
    
    std::cout << "OK" << std::endl;
    return 0;
}
