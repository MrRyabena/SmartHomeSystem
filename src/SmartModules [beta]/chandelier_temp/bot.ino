#include <FastBot.h>

#define BOT_ACTIVE 1
#undef BOT_NAME
#define BOT_NAME "SHS_chandelier_bot"

FastBot bot(CHANDELIER_BOT_TOKEN);

void handleBot(FB_msg &message);

void botSetup()
{

#ifdef BOT_UPDATE_TIME
  bot.setPeriod(BOT_UPDATE_TIME);
#endif


  bot.attach(handleBot);

  bot.setTextMode(FB_HTML);
  botSendNotification("I am started!");

  Serial.println("ok");
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

void botSendNotification(String message)
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


  if (message.text.startsWith("part"))
  {
    String str = message.text.substring(message.text.indexOf(' '));
    uint8_t val = static_cast<uint8_t>(str.toInt());

    switch (val)
    {
    case 1: digitalWrite(PART1_pin, 1); break;
    case 2: digitalWrite(PART2_pin, 1); break;
    default:
      digitalWrite(PART1_pin, 0);
      digitalWrite(PART2_pin, 0);
      break;
    }

    String answer = "Part: ";
    answer += val;
    answer += '.';
    bot.sendMessage(answer, message.chatID);
  }

  else if (message.text.startsWith("on"))
  {
    String str = "on!";
    digitalWrite(PART1_pin, 1);
    digitalWrite(PART2_pin, 1);

    bot.sendMessage(str, message.chatID);
  } else if (message.text.startsWith("off"))
  {
    String str = "off!";
    digitalWrite(PART1_pin, 0);
    digitalWrite(PART2_pin, 0);

    bot.sendMessage(str, message.chatID);
  } else if (message.text.startsWith("temp"))
  {
    String str = "Temp: ";
    str += therm.getTempAverage();
    str += "*C.\n";
    str += analogRead(A0);
    bot.sendMessage(str, message.chatID);
  }
}
