#include "shs_MQTTbus.h"

#include <shs_Random.h>

#include <shs_debug.h>

shs::MQTTbus::MQTTbus(const shs::t::shs_busID_t busID, const Data& data, shs::API* handler, const uint8_t bufsize)
    : DTPbus(busID, handler, bufsize), m_data(data), m_mqtt(m_data.host, m_data.port, [this](const char* topic, const uint8_t* payload, const unsigned length) { this->onCallback(topic, payload, length); }, m_client)
{
    m_mqtt.setServer(m_data.host, m_data.port);
}

void shs::MQTTbus::start()
{
    doutln("starting MQTTbus...");

    //m_mqtt.setCallback([this](char* topic, uint8_t* payload, unsigned length) {});

    shs::Random<uint16_t> rnd;
    rnd.autoSeed();

    String id = "SHS_";
    id += rnd.get();
    if (m_mqtt.connect(id.c_str()))
    {
        doutln("MQTT connected");
        if (m_mqtt.subscribe(m_data.topic, 1)) doutln("MQTT subscribed");
    }
}

void shs::MQTTbus::tick()
{
    // if (m_mqtt.connected()) 
    // {
    //     dsep();
    //     doutln("connection lost");
    //     dsep();
    //     m_tmr_reconnect.reset();
    // }
    // if (m_tmr_reconnect.expired())
    // { start(); doutln("MQTT reconnecting"); }

    if (!m_mqtt.connected()) { start(); }

    m_mqtt.loop();
}

void shs::MQTTbus::stop()
{
    m_mqtt.disconnect();
}

uint8_t shs::MQTTbus::sendPacket(const shs::DTPpacket& packet)
{
    if (packet.empty()) { /*doutln("packet empty");*/ return 0; }
    // dout("state: "); doutln(m_mqtt.state());

    dsep();
    dout("sending packet: ");
    auto r = m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    dout(r);
    auto result = DTPbus::sendPacket(m_mqtt, packet);
    r = m_mqtt.endPublish();
    dout(r);
    doutln(result);
    dout("packet:");
    for (auto x : packet.bc) dout(static_cast<int>(x));
    doutln();
    dsep();
    return result;
}

uint8_t shs::MQTTbus::sendRAW(shs::ByteCollector<>& bc)
{
    m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    auto result = DTPbus::sendRAW(m_mqtt, bc);
    m_mqtt.endPublish();

    return result;
}

uint8_t shs::MQTTbus::sendRAW(shs::ByteCollectorReadIterator<>& it)
{
    m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    auto result = DTPbus::sendRAW(m_mqtt, it);
    m_mqtt.endPublish();

    return result;
}

uint8_t shs::MQTTbus::sendRAW(const uint8_t* data, const uint8_t size)
{
    m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    auto result = DTPbus::sendRAW(m_mqtt, data, size);
    m_mqtt.endPublish();

    return result;
}

void shs::MQTTbus::onCallback(const char* topic, const uint8_t* payload, const unsigned length)
{
    //  doutln("MQTT onCallback");
    if (strcmp(topic, m_data.topic) != 0) return;
    dsep();
    doutln("MQTT message received");
    //dout("Topic: ");
    //doutln(topic);

    dout("data: ");
    for (auto i = 0; i < length; i++) dout(static_cast<int>(payload[i]));
    doutln();
    dsep();
    m_available += length;
    if (m_len == 0)
    {
        m_bc.clear();
        m_len = payload[0];
    }
    if (m_available < m_len - 1) status = Status::packet_is_expected;
    else
    {
        status = Status::packet_received;
        m_available = 0;
        m_len = 0;
    }

    // m_bc.push_back(payload, length);
    m_bc.write(payload, length);

    if (m_handler) processPacket(*m_handler);
}

shs::DTPbus::Status shs::MQTTbus::checkBus()
{
    tick();

    if (status == Status::packet_received || status == Status::packet_processed)
    {
        status = Status::no_data;
        return Status::packet_processed;
    }
    return status;
}
