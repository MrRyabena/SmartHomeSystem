void handleBus() {
  bus.tick();


  if (bus.gotData()) {
    uint8_t buf[BUSbufsize];
    bus.readData(buf);
    
  }
}