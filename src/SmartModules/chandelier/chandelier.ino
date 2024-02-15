#include <SHSlibrary.h>
#include <GyverDimmer.h>
#include <SHSmodule.h>

#define Dpin 12

DimmerBres<Dpin> dim;
IRAM_ATTR void ist();

shs::Processes processes(dtpHandler);

void dtpHandler(shs::DTPdata &d);

void setup()
{
    processes.setup();

    pinMode(14, INPUT);
    attachInterrapt(14, isr, RISING);
    dim.write(0);
}

void loop()
{
    processes.tick();
}

IRAM_ATTR void isr()
{
    dim.tick();
}

void dtpHandler(shs::DTPdata &d)
{
    switch (d.data->buf[0])
    {
    case shs::chandelierAPI::setBrightness:
        dim.write(d.data->buf[1]);
        break;

    default:
        break;
    }
}
