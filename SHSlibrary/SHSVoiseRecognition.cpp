#include "SHSVoiseRecognition.h"

shs::VR::VR(Stream *bus, void (*handler)(shs::ByteCollector &bc))
    : _bus(bus), _handler(handler)
{
}

shs::VR::~VR() {}

shs::VR::checkSystem()
{
    shs::ByteCollector bc;
    bc.add(shs::shsVR::CMD_CHECK_SYSTEM, 1);
}

void shs::VR::recordWithNote(const uint8_t cell, const char *note)
{
    shs::ByteCollector bc;
    bc.add(shs::shsVR::CMD_SIG_TRAIN, 1);
    bc.add(cell);
    for (auto x : note)
        bc.add(x);
}

void shs::VR::loadCmds(shs::ByteCollector &cmds)
{
    bc.addBefore(CMD_LOAD_CMDS, 1);
    _sendData(cmds);
}

uint8_t shs::VR::_sendData(shs::ByteCollector &bc)
{
    bc.addBefore(bc.size() + 1);
    bc.addBefore(shs::shsVR::PACKET_HEAD, 1);
    bc.add(shs::shsVR::PACKET_END, 1);

    _bus->write(bc.buf, bc.buf[1]);
    return bc.buf[1];
}

void shs::VR::_unpackData(shs::ByteCollector &bc)
{
    switch (bc.buf[2])
    {
    case shs::shsVR::CMD_SIG_TRAIN:

        break;

    case shs::shsVR::CMD_ANSW_HINT:
        char str[15]{};
        strncpy(str, &bc.buf[4], bc.buf[1] - 4);
        str[bc.buf[1] - 4] = 0;
        if (!strcmp(str, shs::shsVR::ST_SPEAK_NOW))
            _status = shs::shsVR::Status::speak_now;
        else if (!strcmp(str, shs::shsVR::ST_SPEAK_AGAIN))
            _status = shs::shsVR::Status::speak_again;
        else if (!strcmp(str, shs::shsVR::ST_CANNT_MATCHED))
            _status = shs::shsVR::Status::cannt_matched;
        else if (!strcmp(str, shs::shsVR::ST_SUCCESS))
            _status = shs::shsVR::Status::success;

        break;

    default:
        break;
    }

    if (_handler)
        _handler(bc);
}
