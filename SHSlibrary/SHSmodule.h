#pragma once
#include "SHSconnectWiFi.h"
#include "SHSTcpClient.h"
#include <GyverNTP.h>

#define PORT 50000
namespace shs
{
    class Module;
    extern Module module;

    class Processes;

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
    void generateMac(uint8_t *mac);
    uint8_t serverID{};
    GyverNTP ntp(3, 1800);


    Module(uint8_t modID, void (*errorsHandler)(const shs::Errors e) = nullptr);
    ~Module();

    void error(const shs::Errors e);

private:
    void (*_errorsHandler)(const hs::Errors e)
};

class shs::Processes
{
public:
    shs::TcpClient *tcp;
    shs::DTP *dtp;

    Processes(void (*handler)(shs::DTPdata &));
    ~Processes();

    void setup();
    void tick();

private:
};
