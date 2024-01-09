#include "SHSmodule.h"

shs::Module shs::Module(uint8_t modID)
{
    ID = modID;
}

shs::Module shs::Module(uint8_t modID, (*DTPhandler)((shs::DTPdata &)))
{
    ID = modID;
    uint8_t ip[]{192, 168, 1, modID};
    tcp = new tcp(ip, DTPhandler);
}

shs::Module shs::~Module()
{
    if (tcp != nullptr)
        delete tcp;
}

void shs::Module::setup()
{
    shs::connectWiFi();
    tcp->begin();
}

void shs::Module::tick()
{
    tcp->tick();
}

void shs::Module::error(shs::Errors e)
{
    switch (e)
    {
    case shs::Errors::OK:
        break;

    default:
        break;
    }
}
