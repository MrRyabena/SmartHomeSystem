#pragma once


#include <QCoreApplication>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QAbstractSocket>
#include <shs_settings_private.h>
#include <shs_DTP_API.h>


class TcpClient : public QObject {
    Q_OBJECT

public:
    TcpClient(const QString &host = "192.168.1.174", quint16 port = shs::settings::DEFAULT_TCP_PORT, QObject *parent = nullptr) : QObject(parent) {
        socket = new QTcpSocket(this);

        // Подключаем сигналы
        connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
        connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
        connect(socket, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpClient::onError);
        connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);


        // Подключаемся к серверу
        socket->connectToHost(QHostAddress(host), port);
    }

    Q_INVOKABLE void sendData(const QString &data) {
        if (socket->state() == QAbstractSocket::ConnectedState) {

        } else {
            qDebug() << "Socket is not connected!";
        }
    }

    void sendPacket(const shs::DTPpacket &packet) {
        socket->write(reinterpret_cast<const char*>(packet.bc.getPtr()), packet.bc.size());
        for (auto x : packet.bc) qDebug() << x << ' ';
    }

private slots:
    void onConnected() {
        qDebug() << "Connected to server";

        auto packet = shs::DTP_APIpackets::getInitialPacket(20);
        sendPacket(packet);
        qDebug() << "Sent initial packet";
        socket->flush(); // Убедитесь, что данные отправлены
        //socket->disconnectFromHost(); // Отключаемся после отправки
    }

    void onDisconnected() {
        qDebug() << "Disconnected from server";
        //QCoreApplication::quit(); // Завершаем приложение
    }

      void onError(QAbstractSocket::SocketError socketError) {
          qDebug() << "Socket error:" << socketError; // Выводим код ошибки
                 qDebug() << "Error string:" << socket->errorString(); // Выводим строку ошибки
                 //QCoreApplication::quit();
    }

    void onReadyRead() {
            QByteArray data = socket->readAll();
            qDebug() << "Data received:" << data;
        }

public slots:
    void onSwitchToggled(bool checked) {
        if (checked) {
            shs::ByteCollector<> bc(12);
//            bc.push_back(11, 1);
//            bc.push_back(1, 1);
//            bc.push_back(THIS_ID, 4);
//            bc.push_back(LOAD_ID, 4);
            bc.push_back(2, 1);
            shs::DTPpacket packet(THIS_ID, LOAD_ID, std::move(bc));
            sendPacket(packet);



           // qDebug() << bc.size();
           // socket->write(reinterpret_cast<const char*>(bc.getPtr()), bc.size());
            qDebug() << "On";
        } else {
            shs::ByteCollector<> bc(3);
               bc.push_back(1, 1);
               bc.push_back(1, 2);
               shs::DTPpacket packet(THIS_ID, LOAD_ID, std::move(bc));

               sendPacket(packet);

            qDebug() << "Off";
        }
    }

private:
    QTcpSocket *socket;
    static constexpr shs::t::shs_ID_t THIS_ID{20};
    static constexpr shs::t::shs_ID_t LOAD_ID = shs::t::shs_ID_t(22, 1, 4); // static_cast<uint16_t>(shs::constants::APIids::Load
    static constexpr shs::t::shs_IP_t HOST_IP{"192.168.1.174"};
    static constexpr shs::t::shs_port_t PORT = shs::settings::DEFAULT_TCP_PORT;
};
