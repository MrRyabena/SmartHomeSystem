#pragma once


#include "shs_settings_private.h"

#ifdef SHS_SF_QT

#include <functional>

#include <QObject>
#include <QMqttClient>
#include <QString>
#include <QByteArray>

#include <shs_types.h>
#include <shs_ByteCollector.h>

namespace shs
{
    namespace lib
    {
        namespace qt
        {
            class MQTTclient;
        }
    }
}


class shs::lib::qt::MQTTclient : public QObject
{
    Q_OBJECT
public:
    explicit MQTTclient(QObject * parent, std::function<void(const char* topic, const uint8_t * payload, const unsigned length)> callback);
    explicit MQTTclient(QObject* parent, QString host, uint16_t port, std::function<void(const char* topic, const uint8_t* payload, const unsigned length)> callback);
    ~MQTTclient() = default;

    uint8_t write(const uint8_t* buf, const uint16_t size);
    uint8_t read();
    uint8_t read(uint8_t* buf, const uint16_t size);
    uint16_t available();

    void setHostname(QString host) { m_qmqtt->setHostname(host); }
    void setPort(uint16_t port) { m_qmqtt->setPort(port); }
    void setClientId(QString id) { m_qmqtt->setClientId(id); }
    void setTopick(QMqttTopicName topic) { m_topic = topic; }
    void connectToHost() { m_qmqtt->connectToHost(); }
    void disconnectFromHost() { m_qmqtt->disconnectFromHost(); }
    bool connected() const { return m_connected; }

    void attachCallback(std::function<void(const char* topic, const uint8_t* payload, const unsigned length)> callback) { m_callback = callback; }

    QMqttClient* getQMqttClient() const { return m_qmqtt; }

signals:
    void s_connected();
    void disconnected();
    void errorChanged(QMqttClient::ClientError error);
    void messageReceived();

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorChanged(QMqttClient::ClientError error);
    void onMessageReceived(const QByteArray& message, const QMqttTopicName& topic = QMqttTopicName());

private:
    QMqttClient* m_qmqtt;
    QMqttTopicName m_topic;
    std::function<void(const char* topic, const uint8_t* payload, const unsigned length)> m_callback;
    shs::ByteCollector<> m_buffer;
    bool m_connected;
};

#endif    // #ifdef SHS_SF_QT
