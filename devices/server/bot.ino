void botSetup() {
  bot.attach(parseBot);

  bot.setTextMode(FB_HTML);
  botSendNotification("I am started!");
}

void telegramBot(void *p) {
  while (true) {
    static uint32_t tmr{};

    if (millis() - tmr < BOT_PERIOD) continue;

    xSemaphoreTake(wifi_mutex, portMAX_DELAY);
    bot.tickManual();
    tmr = millis();
    xSemaphoreGive(wifi_mutex);
  }
}

void botSendNotification(const String &message) {
#ifdef BOT_ACTIVE

  bot.sendMessage("<b><u><i>SYSTEM NOTIFICATION!</i></u>\n" + message + "</b>", CHAT_ID);

#endif
}


// void sendAlarm(const String &message) {
//   xSemaphoreTake(wifi_mutex, portMAX_DELAY);
//   abot.sendMessage(message, CHAT_ID);
//   xSemaphoreGive(wifi_mutex);
// }

void parseBot(FB_msg &message) {
  if (message.OTA && message.text.equals(F("/OTA"))) {
    if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0) {
      bot.updateFS();  // update spiffs
    } else {
      bot.update();  // update sketch
    }
  }

  if (message.text.indexOf('@') != -1)
    if (message.text.indexOf(BOT_NAME) != -1)
      message.text.remove(0, strlen(BOT_NAME));
  if (message.text.startsWith("/"))
    message.text.remove(0, 1);

  

  // if (message.text.startsWith(F("braR")))
  // {
  //     String str = message.text.substring(message.text.indexOf(' '));
  //     uint8_t val = static_cast<uint8_t>(str.toInt());
  //     setBraR(val);
  //     String m = "R: ";

  //     m += val;
  //     bot.sendMessage(m, message.chatID);
  // }
  // if (message.text.startsWith(F("braL")))
  // {
  //     String str = message.text.substring(message.text.indexOf(' '));
  //     uint8_t val = static_cast<uint8_t>(str.toInt());
  //     setBraL(val);
  //     String m = "L: ";
  //     m += val;
  //     bot.sendMessage(m, message.chatID);
  // }

  // if (message.text.startsWith(F("getT")))
  // {
  //     getT();
  // }
  // if (message.text.startsWith(F("getPWM")))
  // {
  //     getPWM();
  // }
  // if (message.text.startsWith(F("getRPM")))
  // {
  //     getRPM();
  // }
  // if (message.text.startsWith(F("sunrise")))
  // {
  //     String str = message.text.substring(message.text.indexOf(' '));
  //     dur = static_cast<uint8_t>(str.toInt());
  //     sunrise(dur);
  //     String m = "Sunrise! ";
  //     m += dur;
  //     bot.sendMessage(m, CHAT_ID);
  // }
}
