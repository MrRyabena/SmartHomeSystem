#include "settings.h"


#include <SHSlibrary.h>

#include <FastBot.h>
FastBot bot(BOT_TOCKEN);

#include <GRGB.h>
GRGB strip(COMMON_ANODE, Rp, Gp, Bp);


void setup() {
  connectWiFi();
  botSetup();
  analogWriteResolution(8);
}


void loop() {
  bot.tick();
  RGB();
  
}


