#include <FastBot.h>

FastBot bot(WEATHERSTATION_BOT_TOKEN);

void handleBot(FB_msg &message);

void botSetup() {

#ifdef BOT_UPDATE_TIME
  bot.setPeriod(BOT_UPDATE_TIME);
#endif
  bot.attach(handleBot);

  bot.setTextMode(FB_HTML);
  botSendNotification("I am started!");
}

void telegramBot() {

#ifdef BOT_ACTIVE
  static bool botSetup_flag{};
  if (shs::ControlWiFi::WiFiConnected() && !botSetup_flag) {
    botSetup_flag = true;
    botSetup();
  }
  bot.tick();

#endif
}

void botSendNotification(const String &message) {
#ifdef BOT_ACTIVE

  bot.sendMessage("<b><u><i>SYSTEM NOTIFICATION!</i></u>\n" + message + "</b>", CHAT_ID);

#endif
}



void handleBot(FB_msg &message) {
  if (message.OTA && message.text.equals(F("/OTA"))) {
    if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0) {
      bot.updateFS();  // update spiffs
    } else {
      bot.update();  // update sketch
    }
  }

  auto ind = message.text.indexOf('@');
  if (ind != -1)
    if (message.text.indexOf(BOT_NAME) != -1) message.text.remove(ind, strlen(BOT_NAME + 1));
  if (message.text.startsWith("/")) message.text.remove(0, 1);


  if (message.text.startsWith("getdata")) {
    shs::WeatherStationData wsd;
    WSupdate(wsd);

    String str;
    str.reserve(70);

    str += F("inTemp:    ");
    str += wsd.indoorTemperature;
    str += F("\noutTemp:  ");
    str += wsd.outdoorTemperature;
    str += F("\noutHum:   ");
    str += wsd.outdoorHumidity;
    str += F("\npressure:  ");
    str += wsd.pressure;
    str += F("\ntime:        ");
    str += wsd.time;
    str += F("\nillum:      ");
    str += wsd.illuminance;
    str += F("\nisRain:     ");
    str += wsd.isRain;

    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith("getfile")) {
    bot.sendMessage("Sending...", message.chatID);

    File file = LittleFS.open(WS_FILE_NAME, "r");

    String name = "wsd_";
    name.reserve(15);
    name += ntp.unix();
    name += ".shsf";

    bot.sendFile(file, FB_DOC, name, message.chatID);
    file.close();
  }

  else if (message.text.startsWith("resetfile")) {
    if (message.chatID == CHAT_ID) {
      botSendNotification("Reset file!");
      bot.sendMessage("Sending current file...", message.chatID);
      File file = LittleFS.open(WS_FILE_NAME, "r");

      String name = "wsd_";
      name.reserve(15);
      name += ntp.unix();
      name += ".shsf";

      bot.sendFile(file, FB_DOC, name, message.chatID);
      file.close();

      LittleFS.remove(WS_FILE_NAME) ? botSendNotification("The file has been reset!") : botSendNotification("Error!");
    }
  } else if (message.text.startsWith("timestatus")) {
    String str = "NTP status: ";
    str += ntp.updateNow();
    str += ".\n";
    str += "NTP time: ";
    str += ntp.unix();
    str += "\nbot time: ";
    str += bot.getUnix();

    bot.sendMessage(str, message.chatID);
  }
}
