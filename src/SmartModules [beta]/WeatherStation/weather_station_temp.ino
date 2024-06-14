void WSbegin()
{
    LittleFS.begin();


    ntp.setHost("ntp.msk-ix.ru");
    ntp.begin();
    bme.begin();
    dht.begin();
    pinMode(RAINSENSORpin, INPUT);
    pinMode(A0, INPUT);

    // File file = LittleFS.open(WS_FILE_NAME, "r");
    // if (file)
    // {
    //     shs::WeatherStationData wsd;
    //     shs::CRC32 crc;

    //     file.seek(file.size() - sizeof(wsd) - sizeof(crc.crc));
    //     file.read((uint8_t *) &wsd, sizeof(wsd));
    //     file.read((uint8_t *) &crc.crc, sizeof(crc));

    //     if (crc.crcBuf((uint8_t *) &wsd, sizeof(wsd)) != crc.crc)
    //     {
    //         botSendNotification("Begin file crc error!");
    //         return;
    //     }

    //     auto e = ntp.updateNow();
    //     if (e)
    //     {
    //         String str = "NTP error! Code: ";
    //         str += e;
    //         str += '.';
    //             botSendNotification(str);
    //         return;
    //     }

    //     WS_T = (ntp.unix() - wsd.time) * 1000;
    //     if (WS_T > 600'000) WStick();

    // }
    // file.close();
}

void WSupdate(shs::WeatherStationData &wsd)
{
    wsd.indoorTemperature = bme.readTemperature();

    yield();

    wsd.outdoorTemperature = dht.readTemperature();
    yield();
    wsd.outdoorHumidity = dht.readHumidity();
    yield();

    wsd.pressure = bme.readPressure();
    yield();

    wsd.time = ntp.unix();
    yield();
    //wsd.time = bot.getUnix();
    {
        uint16_t res{};

        static_assert(sizeof(res) == 2);
        static_assert(alignof(res) == 2);
        static_assert(sizeof(wsd.illuminance) == 2);

        for (uint8_t i = 0; i < 20; i++) res += analogRead(A0);
        res /= 20;
        wsd.illuminance = res;
    }
    yield();
    wsd.isRain = !digitalRead(RAINSENSORpin);
}

void WSsave(shs::WeatherStationData &wsd)
{
    File file = LittleFS.open(WS_FILE_NAME, "a");
    if (file)
    {
        shs::CRC32 crc;
        crc.crc = crc.crcBuf((uint8_t *) &wsd, sizeof(wsd));

        file.write((uint8_t *) &wsd, sizeof(wsd));
        file.write((uint8_t *) &crc.crc, sizeof(crc.crc));
        file.close();
    } else bot.sendMessage("ERROR! file", CHAT_ID);
}


void WStick()
{
    static uint64_t tmr{};
    if (millis() - tmr >= WS_T)
    {
        shs::WeatherStationData wsd;
        WSupdate(wsd);
        WSsave(wsd);
        yield();

        tmr = millis();
        WS_T = 600'000;  // 10 minutes

        bot.sendMessage("save", CHAT_ID);
    }
}
