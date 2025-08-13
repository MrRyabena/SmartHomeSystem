#include "shs_AStreamBuf.h"


shs::AStreamBuf shs::serial_ASreamBuf(Serial);

void shs::rd_cio_to_ASerial()
{
    std::cin.rdbuf(&shs::serial_ASreamBuf);
    std::cout.rdbuf(&shs::serial_ASreamBuf);
    std::cerr.rdbuf(&shs::serial_ASreamBuf);
}
