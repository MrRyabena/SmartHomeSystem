#include "SHSVoiseRecognition.h"

shs::VR::VR(Stream *bus, void (*handler)(shs::ByteCollector &bc))
    : _bus(bus), _handler(handler)
{
}

shs::VR::~VR() {}

shs::VR::checkSystem()
{
    shs::ByteCollector bc;
    bc.add(shs::shsVR::CMD_CHECK_SYSTEM);
}

shs::VR::recordWithNote(const uint8_t cell, const char *note)
{
    shs::ByteCollector bc;
    bc.add(shs::shsVR::CMD_SIG_TRAIN);
    bc.add(cell);
    for (auto x : note)
        bc.add(x);
}

uint8_t shs::VR::_sendData(shs::ByteCollector &bc)
{
    bc.addBefore(bc.size() + 1);
    bc.addBefore(shs::shsVR::PACKET_HEAD);
    bc.add(shs::shsVR::PACKET_END);

    _bus->write(bc.buf, bc.buf[1]);
    return bc.buf[1];
}

uint8_t shs::VR::_unpackData(shs::ByteCollector &bc)
{
    switch (bc.buf[2])
    {
    case CMD_SIG_TRAIN:
        
        break;
    }
    if ()
}
