#include <SHSlibrary.h>
#include <GyverDimmer.h>

#define Dpin 12

DimmerBres<Dpin> dim;
IRAM_ATTR void ist();

void setup()
{
    shs::connectWiFi();
    
    pinMode(14, INPUT);
    attachInterrapt(14, isr, RISING);
    dim.write(0);

}

void loop()
{

}

IRAM_ATTR void isr()
{
    dim.tick();
}
