#include "shs_lib_qt_MQTTclient.h"

shs::lib::qt::MQTTclient::MQTTclient(QObject* parent, std::function<void(const char* topic, const uint8_t* payload, const unsigned length)> callback)
    : QObject(parent), m_callback(callback)
{

}

shs::lib::qt::MQTTclient::MQTTclient(QObject* parent, QString host, uint16_t port, std::function<void(const char* topic, const uint8_t* payload, const unsigned length)> callback)
    : QObject(parent), m_callback(callback)
{
    m_qmqtt->setHostname(host);
    m_qmqtt->setPort(port);
}


uint8_t shs::lib::qt::MQTTclient::write(const uint8_t* buf, const uint16_t size)
{
    return m_qmqtt->publish(m_topic, QByteArray(reinterpret_cast<const char*>(buf), size));
}


uint8_t shs::lib::qt::MQTTclient::read()
{
    uint8_t value{};
    m_buffer.get(value, 1);
    return value;
}
uint8_t shs::lib::qt::MQTTclient::read(uint8_t* buf, const uint16_t size)
{
    m_buffer.read(buf, size);
    return size;
}

uint16_t shs::lib::qt::MQTTclient::available()
{
    return m_buffer.readAvailable();
}


void shs::lib::qt::MQTTclient::onConnected()
{
    m_connected = true;
    emit s_connected();
}


void shs::lib::qt::MQTTclient::onDisconnected()
{
    m_connected = false;
    emit disconnected();
}

void shs::lib::qt::MQTTclient::errorChanged(QMqttClient::ClientError error)
{
    emit errorChanged(error);
}

void shs::lib::qt::MQTTclient::onMessageReceived(const QByteArray& message, const QMqttTopicName& topic)
{
    m_buffer.reset();
    m_buffer.write(reinterpret_cast<const uint8_t*>(message.data()), message.length());

    emit messageReceived();
}
