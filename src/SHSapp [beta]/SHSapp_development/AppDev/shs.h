#pragma once

#include <QObject>
//#include <shs_DTP.cpp>
#include <shs_DTP.h>
#include <shs_types.h>
#include <shs_TcpSocket.h>
#include <QDebug>

//#include <memory>
#include <shs_LoadVirtual.h>

class SHS : public QObject
{
    Q_OBJECT
public:
    explicit SHS(QObject* parent = nullptr) : QObject(parent), m_dtp(THIS_ID), m_load(THIS_ID, LOAD_ID, m_dtp)
    {
       m_dtp.attachBus(std::make_unique<shs::TcpSocket>(HOST_IP, PORT, m_dtp.getUniqueBusID()));
       start();
    }

    ~SHS() = default;

    Q_INVOKABLE void start() { m_dtp.start(); qDebug() << "start!"; }
    Q_INVOKABLE void tick()  { m_dtp.tick(); }
    Q_INVOKABLE void stop()  { m_dtp.stop(); }

public slots:
    void onSwitchToggled(bool checked) {
        if (checked) {
           m_load.on(uint8_t(255));
        } else {
           m_load.off();
        }
    }

private:
    static constexpr shs::t::shs_ID_t THIS_ID{20};
    static constexpr shs::t::shs_ID_t LOAD_ID{20, 1};
    static constexpr shs::t::shs_IP_t HOST_IP{"192.168.1.22"};
    static constexpr shs::t::shs_port_t PORT = 5000;

    shs::DTP m_dtp;
    shs::LoadVirtual m_load;
};
