#include <GyverDimmer.h>
#include <GyverNTC.h>
#include <SHSsettings.h>
#include <shs_ControlWiFi.h>

#define Dpin 13
#define INTpin 12

DimmerBres<Dpin> dim;
IRAM_ATTR void ist();

GyverNTC therm(A0, 10000, 3435);



void setup()
{
    pinMode(A0, INPUT);

    pinMode(INTpin, INPUT);
    attachInterrupt(INTpin, isr, RISING);

    shs::ControlWiFi::connectWiFi();

    dim.write(0);
}

void loop()
{
    if (!shs::ControlWiFi::WiFiConnected())
    {
        //dim.write(255);
    } else
    {
        telegramBot();
    }

}

IRAM_ATTR void isr()
{
    dim.tick();
}
