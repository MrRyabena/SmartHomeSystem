#include "TCPstream.h"


uint8_t Api::handler(shs::ByteCollector &bc) {
    shs::DTPpacker parser;
    shs::DTPdata info;

    parser.parseDTP(&bc, info);
    qDebug() << info.from << ' ' << info.apiID;


    bc.readPtr += 3;

    switch (info.apiID) {

    case -2: {
        double value{};
        int val;
        bc.get(val, 2);
        value = getThermTemp(val);
        qDebug() << "Temp: " << val << ' ' << value;
        m_w->ThermBuf.push_back(value);
    }
        break;
//    case photo:
//    {
//        double value{};
//        bc.get(value, 4);
//        m_w->PhotoBuf.push_back(value);
//    }
//        break;
    }

    return 0;
}




