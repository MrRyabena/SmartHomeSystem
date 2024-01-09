/*
  Smart Home System Data Transmission Protocol
*/

#pragma once
#include <Arduino.h>
#include "SHSalgoritm.h"
#include "SHSByteCollector.h"
#define DTP_OFFSETbeg 3

namespace shs
{
    enum DTPcommands : uint8_t;
    struct DTPdata;
    class DTP;

};

enum shs::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

struct shs::DTPdata
{
    uint8_t from{};
    uint8_t to{};
    uint8_t datasize{};
    shs::ByteCollector *data{};
};

class shs::DTP
{
public:
    DTP(Stream *bus, void (*callback)(shs::DTPdata &), uint8_t ID = shs::module.ID);

    ~DTP();

    uint8_t checkBus(uint8_t *len);

    uint8_t sendPacket(shs::ByteCollector *bc, uint8_t to);
    uint8_t sendPacket(shs::ByteCollector *bc, uint8_t to, uint8_t from);

    uint8_t packDTP(shs::ByteCollector *bc, uint8_t to);
    uint8_t packDTP(shs::ByteCollector *bc, uint8_t to, uint8_t from);
    uint8_t checkDTP(shs::ByteCollector *bc);
    uint8_t parseDTP(shs::ByteCollector *bc, void (*callback)(shs::DTPdata &));

private:
    uint8_t _ID{};
    Stream *_bus{};
    void (*_callback)(shs::DTPdata &){};
    uint8_t _len{};
};
