#include <memory>

#define DEBUG
#include <shs_debug.h>
#include <shs_settings_private.h>

#include <ESP8266WiFi.h>

#include <shs_ControlWiFi.h>
#include <shs_LoadSwitch.h>
#include <shs_Load_API.h>

#include <shs_DTP.h>

#include <shs_TcpServer.h>
#include <shs_UDP.h>
#include <shs_DTPdiscover.h>
#include <shs_DTPbus.h>
#include <shs_DTPdiscover.h>


#include "settings.h"
#include "shs_APIprint.h"

shs::LoadSwitch load(LED_BUILTIN);

shs::DTP dtp(THIS_ID);


shs::TcpServer server(PORT, dtp);
shs::APIprint api_print(0);
shs::DTPdiscover discover(THIS_ID);


//shs::UDP udp;
//shs::UdpBroadcastBus brBus(shs::settings::DEFAULT_UDP_PORT, 0);


void setup() {
  Serial.begin(115200);

  doutln();
  doutln(shs::ControlWiFi::connectWiFiWait());
  shs::ControlWiFi::setHostname("Load_Test");
  doutln(WiFi.localIP());

  dtp.attachAPI(std::make_unique<shs::Load_API>(load, LOAD_ID));

  discover.start();

  server.start();
  dtp.start();

  load.setup();

  load.off();
  delay(2000);
  load.on();


  doutln("final");
}


void loop() {
  server.tick();
  dtp.tick();
  discover.tick();
}
