

uint8_t sunrise(uint8_t duration) {

  if (duration) {
    static uint32_t tmr{};
    static uint32_t tstart{};
    static uint8_t sunVal{};
    if (!tmr && dur) tstart = millis();
    if (millis() - tmr >= (uint32_t)(duration * 60000) >> 8) {
    
      ByteCollector col(8);

      col.add(lapi::analogSetPin, 1);
      col.add<uint8_t>(2, 1);
      col.add(BRARpin, 1);
      col.add(++sunVal, 1);
      col.add(BRALpin, 1);
      col.add(sunVal, 1);


      dtp.sendBuf(LIGHTER_ID, col.buf, col.size());



      tmr = millis();
      String str = "";
      str += sunVal;
      //bot.sendMessage(str, CHAT_ID);
      if (sunVal == 255) {
        dur = 0;
        tstart = 0;
        sunVal = 0;
      }
    }
  }
  return duration;
}
