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


  if (message.text.startsWith("colorWheel")) {
    String str = "colorWheel!";
    RGBmode = 2;
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("fire")) {
    String str = "fire!";
    RGBmode = 1;
    bot.sendMessage(str, message.chatID);
  } else if (message.text.startsWith("off")) {
    String str = "off!";
    RGBmode = 0;
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("red")) {
    String str = "red!";
    RGBmode = 10;
    strip.setRGB(255, 0, 0);
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("green")) {
    String str = "green!";
    RGBmode = 10;
    strip.setRGB(0, 255, 0);
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("blue")) {
    String str = "red!";
    RGBmode = 10;
    strip.setRGB(0, 0, 255);
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("cyan")) {
    String str = "cyan!";
    RGBmode = 10;
    strip.setRGB(0, 255, 255);
    bot.sendMessage(str, message.chatID);
  }

    else if (message.text.startsWith("purple")) {
    String str = "purple!";
    RGBmode = 10;
    strip.setRGB(255, 0, 255);
    bot.sendMessage(str, message.chatID);
  }


  else if (message.text.startsWith("fadeT")) {
    uint16_t val = message.text.substring(message.text.indexOf(' ')).toInt();

    String str = "fadeT: ";
    str += val;

    strip.setFadePeriod(val);
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("fade")) {
    bool val = static_cast<bool>(message.text.substring(message.text.indexOf(' ')).toInt());

    String str = "fade: ";
    str += val;

    strip.fadeMode(val);
    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("br")) {
    uint16_t val = message.text.substring(message.text.indexOf(' ')).toInt();

    String str = "bright: ";
    str += val;

    strip.setBrightness(val);
    bot.sendMessage(str, message.chatID);
  }
}
