#include "settings.h"
#include "lighterAPI.h"

#include <shs_ID.h>
#include <shs_types.h>
#include <shs_DTP.h>
#include <shs_DTPbus.h>
#include <shs_DTPpacket.h>
#include <shs_API.h>

#include <shs_ControlWiFi.h>

#include <TableAPI.h>

#include <shs_TcpClient.h>

const shs::t::shs_ID_t THIS_ID(5);


shs::DTPbus l_bus(Serial, THIS_ID);
shs::DTP dtp



#include <FastBot.h>
FastBot bot(BOT_TOKEN);





uint8_t dur{};

void setup() {
  Serial.begin(BUSspeed);
  
  shs::ControlWiFi::connectWiFiWait();
 
  botSetup();
}

void loop() {
  
  bot.tick();
  client.tick();
  sunrise(dur);
  handleBus();
}
