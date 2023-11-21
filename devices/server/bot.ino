enum TBotCommands : uint8_t
{
  nocommand,
  start,
  help,
};
using tbc = TBotCommands;

void botSetup()
{
  bot.attach(parseBot);

  bot.setTextMode(FB_HTML);
  botSendNotification("I am started!");
}

void telegramBot(void *p)
{
  while (true)
  {
    static uint32_t tmr{};

    if (millis() - tmr < BOT_PERIOD)
      continue;

    xSemaphoreTake(wifi_mutex, portMAX_DELAY);
    bot.tickManual();
    tmr = millis();
    xSemaphoreGive(wifi_mutex);
  }
}

void botSendNotification(const String &message)
{
#ifdef BOT_ACTIVE

  bot.sendMessage("<b><u><i>SYSTEM NOTIFICATION!</i></u>\n" + message + "</b>", CHAT_ID);

#endif
}

// void sendAlarm(const String &message) {
//   xSemaphoreTake(wifi_mutex, portMAX_DELAY);
//   abot.sendMessage(message, CHAT_ID);
//   xSemaphoreGive(wifi_mutex);
// }

void parseBot(FB_msg &message)
{
  if (message.OTA && message.text.equals(F("/OTA")))
  {
    if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0)
    {
      bot.updateFS(); // update spiffs
    }
    else
    {
      bot.update(); // update sketch
    }
  }

  if (message.text.indexOf('@') != -1)
    if (message.text.indexOf(BOT_NAME) != -1)
      message.text.remove(0, strlen(BOT_NAME));
  if (message.text.startsWith("/"))
    message.text.remove(0, 1);

  shsFS.open(F("/data/bot/commands.txt"));
  TBotCommands command{};
  uint8_t counter{};
  while (shsFS._file->position < shsFS._file->size())
  {
    String str = shsFS.readBefore('\n');
    while (str.indexOf('|') > 1)
      if (message.text.startsWhith(str.substring(0, shsFS.indexOf('|'))))
      {
        command = static_cast<TBotCommands>(counter);
        goto out;
      }

    counter++;
  }
out:
  shsFS.close();

  switch (command)
  {
  case tbc::nocommand:
    break;
  case tbc::start:
  {
    shsFS.open(F("/data/bot/start.txt"));
  }
  break;
  default:
    break;
  }
  
}
