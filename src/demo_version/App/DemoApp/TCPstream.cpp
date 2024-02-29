#include "TCPstream.h"


uint8_t Api::handler(shs::ByteCollector &bc) {
    shs::DTPpacker parser;
    shs::DTPdata info;

    parser.parseDTP(&bc, info);


    bc.readPtr++;

    switch (*(bc.readPtr - 1)) {
    using namespace shs::config::SmartServerAPI;

    case therm: {
        double value{};
        bc.get(value, 4);
        m_w->ThermBuf.push_back(value);
    }
        break;
    case photo:
    {
        double value{};
        bc.get(value, 4);
        m_w->PhotoBuf.push_back(value);
    }
        break;
    }

    return 0;
}
