#include "SHSTcpClient.h"

void shs::TcpClient::tick()
{
    if (!client && !client.connected())
        return;

    if (millis() - _tmr >= SILENCE_TIMEOUT)
        ;
}
