void botSetup() {
#ifdef BOT_UPDATE_TIME
  bot.setPeriod(BOT_UPDATE_TIME);
#endif


  bot.attach(handleBot);

  bot.setTextMode(FB_HTML);
  botSendNotification("I am started!");

  Serial.println("ok");
}

void telegramBot() {

#ifdef BOT_ACTIVE

  bot.tick();

#endif
}

void botSendNotification(String message) {
#ifdef BOT_ACTIVE

  bot.sendMessage("<b><u><i>SYSTEM NOTIFICATION!</i></u>\n" + message + "</b>", CHAT_ID);

#endif
}




void handleBot(FB_msg& message) {
    if (message.OTA && message.text.equals(F("/OTA"))) {
    if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0) {
      bot.updateFS();  // update spiffs
    } else {
      bot.update();  // update sketch
    }
  }

  if (message.text.indexOf('@') != -1)
    if (message.text.indexOf(BOT_NAME) != -1) message.text.remove(0, strlen(BOT_NAME));
  if (message.text.startsWith("/")) message.text.remove(0, 1);



  if (message.text.startsWith(F("braR"))) {
    String str = message.text.substring(message.text.indexOf(' '));
    uint8_t val = static_cast<uint8_t>(str.toInt());
    setBraR(val);
    String m = "R: ";

    m += val;
    bot.sendMessage(m, message.chatID);
  }
  if (message.text.startsWith(F("braL"))) {
    String str = message.text.substring(message.text.indexOf(' '));
    uint8_t val = static_cast<uint8_t>(str.toInt());
    setBraL(val);
    String m = "L: ";
    m += val;
    bot.sendMessage(m, message.chatID);
  }
}
