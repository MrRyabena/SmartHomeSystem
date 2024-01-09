#pragma once
#include "SHSconnectWiFi.h"
#include "SHSTcpClient.h"

namespace shs
{
    class Module;
    Module module;
    enum Errors;
}

enum shs::Errors : uint8_t
{
    OK,
    DTPtimeout,
    DTPcrc,
};

class shs::Module
{
public:
    uint8_t ID{};
    TcpClient *tcp{};
    Module(uint8_t modID);
    Module(uint8_t modID, (*DTPhandler)((shs::DTPdata &)));
    ~Module();
    void setup();
    void tick();

    void error(shs::Errors e);

private:
};
