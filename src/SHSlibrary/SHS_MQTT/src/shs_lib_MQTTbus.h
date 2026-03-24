#pragma once

#include <vector>
#include <initializer_list>
#include <stdint.h>
#include <Arduino.h>

#include <PubSubClient.h>

#include <shs_settings_private.h>
#if defined(SHS_SF_ESP8266)
#include <ESP8266WiFi.h>
#elif defined(SHS_SF_ESP32)
#include <WiFi.h>
#endif

#include <shs_Process.h>
#include <shs_DTPbus.h>
#include <shs_types.h>
#include <shs_ProgramTimer.h>

namespace shs
{
    class MQTTbus;
}

class shs::MQTTbus : public shs::Process, public shs::DTPbus
{
public:
    struct Data
    {
        Data(const char* set_topic)
        {
            strcpy(this->topic, set_topic);
        }

        char topic[32];
        char host[32] = "broker.mqtt-dashboard.com";
        uint16_t port = 1883;
    };

    MQTTbus(const shs::t::shs_busID_t busID, const Data& data, shs::API* handler = nullptr, const uint8_t bufsize = 32);
    ~MQTTbus() override = default;

    void onCallback(const char* topic, const uint8_t* payload, const unsigned length);

    bool isActive() const override { return true; } // TODO

    Status checkBus() override;

    uint8_t sendPacket(const shs::DTPpacket& packet) override;
    uint8_t sendRAW(shs::ByteCollector<>& bc) override;
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override;
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override;

    void start() override;
    void tick() override;
    void stop() override;

private:
    WiFiClient m_client;
    PubSubClient m_mqtt;
    shs::ProgramTimer m_tmr_reconnect{10000};
    Data m_data;
    uint8_t m_available{};
};
