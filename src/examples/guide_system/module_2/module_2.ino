#include <gs_config.h>

#include <memory>

#include <shs_Network.hpp>
#include <shs_DTP.hpp>

#include <shs_Load.hpp>

shs::LoadSwitchReversed load(LED_BUILTIN);


shs::DTP dtp(shs::config::Module_2::MODULE_ID);
shs::TcpServer server(shs::settings::DEFAULT_TCP_PORT, dtp);
shs::DTPdiscover discover(shs::config::Module_2::MODULE_ID);


void setup()
{
    shs::ControlWiFi::connectWiFiWait();

    load.setup();

    dtp.attachAPI(std::make_unique<shs::Load_API>(load, shs::t::shs_ID_t(shs::config::Module_2::MODULE_ID, shs::config::Module_2::LOAD)));

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
