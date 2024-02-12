#pragma once

#include <Arduino.h>
#include "ByteCollector.h"

namespace shs
{
    class VR;
    namespace shsVR;
};

namespace shs::shsVR
{
#define PACKET_HEAD 0xAA
#define PACKET_END 0x0A

#define CMD_CHECK_SYSTEM 0x00
#define CMD_CHECK_BSR 0x01

#define CMD_SIG_TRAIN 0x21


#define ST_CANNT_MATCHED                                                                  \
    {                                                                                     \
        0x43, 0x61, 0x6E, 0x6E, 0x27, 0x74, 0x20, 0x6D, 0x61, 0x74, 0x63, 0x68, 0x65, 0x6 \
    }

    enum Status;

};

enum shs::shsVR::Status : uint8_t
{
    off,
    speak,

};

class shs::VR
{
public:
    VR(Stream *bus, void (*handler)(shs::ByteCollector &bc) = nullptr);
    ~VR();
    void recordWithNote(const uint8_t cell, const char *note);

private:
    uint8_t _status{};
    uint8_t _sendData(shs::ByteCollector &bc);
    uint8_t _unpackData(shs::ByteCollector &bc);
    Stream *_bus{};
    void (*_handler)(shs::ByteCollector &bc);

    void checkSystem();
};
