#include <FastBot.h>

FastBot bot(SMARTPC_BOT_TOKEN);

void handleBot(FB_msg &message);

void botSetup()
{

#ifdef BOT_UPDATE_TIME
  bot.setPeriod(BOT_UPDATE_TIME);
#endif
  bot.attach(handleBot);

  bot.setTextMode(FB_HTML);
  botSendNotification("I am started!");
}

void telegramBot()
{

#ifdef BOT_ACTIVE
  static bool botSetup_flag{};
  if (shs::ControlWiFi::WiFiConnected() && !botSetup_flag)
  {
    botSetup_flag = true;
    botSetup();
  }
  bot.tick();

#endif
}

void botSendNotification(const String &message)
{
#ifdef BOT_ACTIVE

  bot.sendMessage("<b><u><i>SYSTEM NOTIFICATION!</i></u>\n" + message + "</b>", CHAT_ID);

#endif
}



void handleBot(FB_msg &message)
{
  if (message.OTA && message.text.equals(F("/OTA")))
  {
    if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0)
    {
      bot.updateFS();  // update spiffs
    } else
    {
      bot.update();  // update sketch
    }
  }

  auto ind = message.text.indexOf('@');
  if (ind != -1)
    if (message.text.indexOf(BOT_NAME) != -1) message.text.remove(ind, strlen(BOT_NAME + 1));
  if (message.text.startsWith("/")) message.text.remove(0, 1);


  if (message.text.startsWith(F("onPC")))
  {
    if (message.chatID != CHAT_ID)
    {
      bot.sendMessage(F("Error: access is denied."), message.chatID);
      goto endif;
    }

    if (PCstatus)
    {
      bot.sendMessage(F("PC already started."), message.chatID);
      goto endif;
    }

    PCswitch();

    String str = F("PC is starting..., status: ");
    str += PCstatus();
    str += '.';

    bot.sendMessage(str, message.chatID);
  }

  else if (message.text.startsWith(F("offPC")))
  {
    if (message.chatID != CHAT_ID)
    {
      bot.sendMessage(F("Error: access is denied."), message.chatID);
      goto endif;
    }

    if (!PCstatus)
    {
      bot.sendMessage(F("PC already stopped."), message.chatID);
      goto endif;
    }

    PCswitch();

    bot.sendMessage(F("PC is stopping..."), message.chatID);
  }

  else if (message.text.startsWith(F("PCstatus")))
  {
    if (message.chatID == CHAT_ID)
    {
      if (message.chatID != CHAT_ID)
      {
        bot.sendMessage(F("Error: access is denied."), message.chatID);
        goto endif;
      }

      String str = F("PC status: ");
      str += PCstatus();
      str += '.';

      bot.sendMessage(str, message.chatID);
    }
  }

endif: return;
}
