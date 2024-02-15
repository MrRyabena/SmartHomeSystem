#include "SHSmodule.h"

shs::Module shs::module = Module();

shs::Module shs::Module(uint8_t modID)
{
    ID = modID;
}

shs::Module::Module(uint8_t modID, void (*errorsHandler)(const shs::Errors e))
{
    ID = modID;
    _errorsHandler = errorsHandler;
}

shs::Module::~Module()
{
}

void shs::Module::error(const shs::Errors e)
{
    switch (e)
    {
    case shs::Errors::OK:
        break;

    default:
        break;
    }
    if (_errorsHandler != nullptr)
        _errorsHandler(e);
}

shs::Processes::Processes(void (*handler)(shs::DTPdata &))
    : tcp(new shs::TcpClient), dtp(new shs::DTP(tcp, handler))
{
}

shs::Processes::~Processes()
{
    delete dtp;
    delete tcp;
}

void shs::Processes::setup()
{
    shs::connectWiFi();
    tcp->connect(serverID, PORT);
}

void shs::Processes::tick()
{
    dtp->tick();
    shs::module.ntp.tick();
}
