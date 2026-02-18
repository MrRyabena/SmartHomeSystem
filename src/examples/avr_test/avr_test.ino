#include <shs_LoadSwitch.h>
#include <shs_Load_API.h>
#include <shs_DTPstreamBus.H>
#include <shs_types.h>
#define SHS_SF_DEBUG
#include <shs_debug.h>


shs::LoadSwitch load(13);
shs::Load_API load_api(load, 0);
shs::DTPstreamBus bus(Serial, 0, &load_api);




void setup()
{
    dinit();

    load.setup();
    load.off();

    bus.start();
}


void loop()
{
    bus.tick();
}
