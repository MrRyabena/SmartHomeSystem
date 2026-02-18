#include <shs_lib_DS18.h>
#define SHS_SF_DEBUG
#include <shs_debug.h>


static constexpr auto pin = D4;

void setup()
{
    dinit();
    shs::DS18 ds(pin);

    ds.setup();
    
    for (auto i = 0; i < 10; i++)
    {
    ds.update();

    while (ds.isUpdated() == false) { delay(1000); dout(ds.getStatus()); dout(' '); dout(ds.gds.isWaiting()); dout(' '); dout(ds.gds.ready()); doutln(); }
    
    dsep();
    doutln(ds.getStatus());
    doutln(ds.isUpdated());
    doutln(ds.getValueD());

    dsep();
    delay(6000);
    }
}

void loop() {}
