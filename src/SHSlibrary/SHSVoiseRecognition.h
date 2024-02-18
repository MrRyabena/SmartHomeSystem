#pragma once

#include <Arduino.h>
#include "SHSByteCollector.h"

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
#define CMD_LOAD_CMDS 0x30

#define CMD_ANSW_HINT 0x0A

#ifndef ESP_H
#define ST_SPEAK_NOW "Speak now"
#define ST_SPEAK_AGAIN "Speak again"
#define ST_CANNT_MATCHED "Cann't matched"
#define ST_SUCCESS "Success"
#else
#define ST_SPEAK_NOW F("Speak now")
#define ST_SPEAK_AGAIN F("Speak again")
#define ST_CANNT_MATCHED F("Cann't matched")
#define ST_SUCCESS F("Success")
#endif

    enum Status;

};

enum shs::shsVR::Status : uint8_t
{
    off,
    speak_now,
    speak_again,
    cannt_matched,
    success,

};

class shs::VR
{
public:
    VR(Stream *bus, void (*handler)(shs::ByteCollector &bc) = nullptr);
    ~VR();
    void recordWithNote(const uint8_t cell, const char *note);
    void loadCmds(shs::ByteCollector &cmds);
    shs::shsVR::Status getStatus() { return _status }

private:
    shs::shsVR::Status _status{};
    uint8_t _sendData(shs::ByteCollector &bc);
    void _unpackData(shs::ByteCollector &bc);
    Stream *_bus{};
    void (*_handler)(shs::ByteCollector &bc);

    void checkSystem();
};
