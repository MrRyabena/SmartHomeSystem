#include "shs_lib_MQTTbus.h"

#include <shs_Random.h>
#include <shs_debug.h>
#include <QByteArray>


shs::lib::MQTTbus::MQTTbus(
#ifdef SHS_SF_QT
    QObject* parent,
#endif
    const shs::t::shs_busID_t busID,
    const Data& data,
    shs::API* handler,
    const uint8_t bufsize)
    :
#ifdef SHS_SF_QT
    QObject(parent),
#endif 
    DTPbus(busID, handler, bufsize),
    m_data(data),
#if defined(SHS_SF_ESP)
    m_mqtt(this, m_data.host, m_data.port,
    [this](const char* topic, const uint8_t* payload, const unsigned length) {
        this->onCallback(topic, payload, length);
    },
           m_client
)
#elif defined(SHS_SF_QT)
m_mqtt(this)
#endif
{
#if defined(SHS_SF_ESP)
    m_mqtt.setServer(m_data.host, m_data.port);
#elif defined(SHS_SF_QT)
    m_mqtt.setHostname(m_data.host);
    m_mqtt.setPort(m_data.port);

    // connect(m_mqtt, &QMqttClient::connected, this, );
    connect(m_mqtt, &QMqttClient::messageReceived, this, onCallback);
#endif
}

void shs::lib::MQTTbus::start()
{
    doutln("starting MQTTbus...");

    //m_mqtt.setCallback([this](char* topic, uint8_t* payload, unsigned length) {});

    shs::Random<uint16_t> rnd;
    rnd.autoSeed();


#if defined(SHS_SF_ESP)
    String id = F("SHS_");
    id += rnd.get();
    if (m_mqtt.connect(id.c_str()))
    {
        doutln("MQTT connected");
        if (m_mqtt.subscribe(m_data.topic, 1)) doutln("MQTT subscribed");
    }
#elif defined(SHS_SF_QT)
    m_mqtt.setClientId("SHS_" + QString::number(rnd.get()));
    m_mqtt.connectToHost();
    m_mqtt.subscribe(QMqttTopicFilter(QString(m_data.topic)), 1);
#endif
}

void shs::lib::MQTTbus::tick()
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

#if !defined(SHS_SF_QT)
    if (!m_mqtt.connected()) { start(); }

    m_mqtt.loop();
#endif
}

void shs::lib::MQTTbus::stop()
{
    m_mqtt.disconnect();
}

uint8_t shs::lib::MQTTbus::sendPacket(const shs::DTPpacket& packet)
{
    if (packet.empty()) { /*doutln("packet empty");*/ return 0; }
    // dout("state: "); doutln(m_mqtt.state());

    dsep();
    dout("sending packet: ");
        doutln("");
    dout("packet:");
    for (auto x : packet.bc) dout(static_cast<int>(x));

    dsep();
#if defined(SHS_SF_ESP)
    auto r = m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    dout(r);

    auto result = DTPbus::sendPacket(m_mqtt, packet);

    r = m_mqtt.endPublish();
    dout(r);
    doutln(result);


    return result;
#elif defined(SHS_SF_QT)
    return sendRAW(packet.bc.getPtr(), packet.bc.size());
#endif
}

uint8_t shs::lib::MQTTbus::sendRAW(shs::ByteCollector<>& bc)
{
#if defined(SHS_SF_ESP)
    m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    auto result = DTPbus::sendRAW(m_mqtt, bc);
    m_mqtt.endPublish();
    return result;
#elif defined(SHS_SF_QT)
    return sendRAW(bc.getPtr(), bc.size());
#endif
}

uint8_t shs::lib::MQTTbus::sendRAW(shs::ByteCollectorReadIterator<>& it)
{
#if defined(SHS_SF_ESP)
    m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    auto result = DTPbus::sendRAW(m_mqtt, it);
    m_mqtt.endPublish();
    return result;
#endif

    return sendRAW(&it, it.size());

}

uint8_t shs::lib::MQTTbus::sendRAW(const uint8_t* data, const uint8_t size)
{
#if defined(SHS_SF_ESP)
    m_mqtt.beginPublish(m_data.topic, strlen(m_data.topic), 1);
    auto result = DTPbus::sendRAW(m_mqtt, data, size);
    m_mqtt.endPublish();
    return result;
#elif defined(SHS_SF_QT)
    return m_mqtt.publish(QMqttTopicName(QString(m_data.topic)), QByteArray(reinterpret_cast<const char*>(data), size));
#endif
}

void shs::lib::MQTTbus::onCallback(const char* topic, const uint8_t* payload, const unsigned length)
{
    //  doutln("MQTT onCallback");
    if (strcmp(topic, m_data.topic) != 0) return;
    dsep();
    doutln("MQTT message received");
    //dout("Topic: ");
    //doutln(topic);

    dout("data: ");
    for (auto i = 0; i < length; i++) dout(static_cast<int>(payload[i]));
    doutln("");
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

shs::DTPbus::Status shs::lib::MQTTbus::checkBus()
{
    tick();

    if (status == Status::packet_received || status == Status::packet_processed)
    {
        status = Status::no_data;
        return Status::packet_processed;
    }
    return status;
}
