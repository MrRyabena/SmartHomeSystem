#include <gs_config.h>

#include <memory>

#include <shs_Network.hpp>
#include <shs_DTP.hpp>

#include <shs_Load.hpp>
#define SHS_SF_DEBUG
#include <shs_debug.h>

shs::LoadSwitchReversed load(LED_BUILTIN);


shs::DTP dtp(shs::config::Module_2_load::MODULE_ID);
shs::TcpServer server(shs::settings::DEFAULT_TCP_PORT, dtp);
shs::DTPdiscover discover(shs::config::Module_2_load::MODULE_ID);


void setup()
{
    dinit();

    doutln(shs::ControlWiFi::connectWiFiWait());

    load.setup();
    load.off();

    dtp.attachAPI(std::make_unique<shs::Load_API>(load,
        shs::t::shs_ID_t(shs::config::Module_2_load::MODULE_ID, shs::config::Module_2_load::LOAD)));

    dtp.start();
    server.start();
    discover.start();
}


void loop()
{
    dtp.tick();
    server.tick();
    discover.tick();
}
